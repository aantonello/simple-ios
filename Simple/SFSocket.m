/**
 * \file
 * Defines the SFSocket Objective-C interface class.
 *
 * \author  Alessandro Antonello aantonello@paralaxe.com.br
 * \date    March 14, 2013
 * \since   Simple Framework 1.1
 *
 * \copyright
 * This file is provided in hope that it will be useful to someone. It is
 * offered in public domain. You may use, modify or distribute it freely.
 *
 * The code is provided "AS IS". There is no warranty at all, of any kind. You
 * may change it if you like. Or just use it as it is.
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/select.h>
#include <sys/errno.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#import "sfstd.h"
#import "SFStream.h"
#import "SFSocket.h"
#import "sfdebug.h"
#import "SFString.h"

/* ===========================================================================
 * SFSocket EXTENSION
 * ======================================================================== */
@interface SFSocket () {
    socket_t m_sd;
    error_t  m_error;
}
@end

/* ===========================================================================
 * SFSocket IMPLEMENTATION
 * ======================================================================== */
@implementation SFSocket
// Properties
// @property (nonatomic, readonly) error_t error;//{{{
@synthesize error = m_error;
//}}}

// Attributes
// - (intptr_t)available;//{{{
- (intptr_t)available
{
    size_t available = 0;
    intptr_t  result = (intptr_t)ioctl(m_sd, FIONREAD, &available);

    m_error = 0;
    if (result < 0) {
        m_error = errno;
        return result;
    }
    return (intptr_t)available;
}
//}}}

// Connection
// - (error_t)open:(NSString*)address port:(NSUInteger)port;//{{{
- (error_t)open:(NSString*)address port:(NSUInteger)port
{
    struct sockaddr_in in_addr;
    error_t result;
    int blockModeOff = TRUE;

    const char* addr = [address utf8Array];     /* SFString */

    m_error = 0;

    /* Check where we have an URL or IP. */
    if (isdigit(*addr))
        in_addr.sin_addr.s_addr = inet_addr( addr );
    else
    {
        struct hostent* host = gethostbyname( addr );
        if (host == NULL) {
            switch (h_errno) {
            case HOST_NOT_FOUND: m_error = ENETDOWN; break;
            case TRY_AGAIN:      m_error = EHOSTUNREACH; break;
            case NO_RECOVERY:    m_error = ECONNREFUSED; break;
            default:             m_error = ENETUNREACH;
            }
            return m_error;
        }
        in_addr.sin_addr.s_addr = *(uint32_t *)host->h_addr_list[0];
    }

    /* Completes the connection address. */
    in_addr.sin_port   = htons((uint16_t)port);
    in_addr.sin_family = AF_INET;

    m_sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_sd < 0) {
        return m_error = errno;
    }

    /* Set the 'non-block' option so we connect in background. */
    ioctl(m_sd, FIONBIO, &blockModeOff);

    /* In the iOS 5 and later, we need to cancel the SIGPIPE signal. */
    setsockopt(m_sd, SOL_SOCKET, SO_NOSIGPIPE, &blockModeOff, sizeof(int));

    sfdebug("SFSocket::connect('%s', %u)\n", inet_ntoa(in_addr.sin_addr), port);
    result = connect(m_sd, (struct sockaddr*)&in_addr, sizeof(struct sockaddr_in));
    if (result == 0) {
        return result;
    }
    if (result < 0) {
        m_error = errno;
        result = m_error;
    }

    if ((result == EWOULDBLOCK) || (result == EINPROGRESS)) {
        m_error = EINPROGRESS;
        return m_error;
    }
    m_error = result;       /* "result" has an error number. */

    close(m_sd);
    m_sd = -1;
    return result;
}
//}}}
// - (error_t)isReady;//{{{
- (error_t)isReady
{
    struct timeval tmv = { 0, 0 };
    struct fd_set fdsw;             /* Write set. */
    struct fd_set fdse;             /* Error set. */

    FD_ZERO( &fdse );
    FD_ZERO( &fdsw );
    FD_SET(m_sd, &fdse);
    FD_SET(m_sd, &fdsw);

    m_error = select((m_sd + 1), NULL, &fdsw, &fdse, &tmv);
    if (m_error == 0)
    {
        /* Timed out. */
        return m_error = EINPROGRESS;
    }
    else if (m_error > 0)
    {
        if (FD_ISSET(m_sd, &fdsw)) {
            return m_error = 0;
        } else {
            int value = 0;
            socklen_t size = sizeof(int);

            m_error = getsockopt(m_sd, SOL_SOCKET, SO_ERROR, &value, &size);
            if (m_error == 0) {
                return m_error = value;
            }
        }
    }

    /* An error was found. The connection could not be made. */
    m_error = errno;
    close(m_sd);
    m_sd = -1;
    return m_error;
}
//}}}

// Communication
// - (BOOL)send:(NSData*)data;//{{{
- (BOOL)send:(NSData*)data
{
    return [self send:[data bytes]  ofLength:[data length]];
}
//}}}
// - (BOOL)send:(const void*)data ofLength:(size_t)length;//{{{
- (BOOL)send:(const void*)data ofLength:(size_t)length
{
    m_error = 0;
    if (send(m_sd, data, length, 0) < 0) {
        m_error = errno;
        return FALSE;
    }
    return TRUE;
}
//}}}
// - (intptr_t)read:(void*)buffer ofLength:(size_t)size;//{{{
- (intptr_t)read:(void*)buffer ofLength:(size_t)size
{
    intptr_t available = [self available];
    if (available < 0) return -1;       /* The error property was already filled. */
    if (available == 0) return 0;       /* Idem. */

    if (size > (size_t)available)
        size = (size_t)available;

    available = recv(m_sd, buffer, size, 0);
    if (available == 0)
    {
        m_error = ESHUTDOWN;        /* Connection shutdown by the peer. */
        close(m_sd);
        m_sd = -1;
        return -1;
    }
    else if (available < 0)
        m_error = errno;            /* Another kind of error. */
    return available;
}
//}}}
// - (intptr_t)read:(NSMutableData*)buffer;//{{{
- (intptr_t)read:(NSMutableData*)buffer
{
    intptr_t available = [self available];

    if (available < 0) return -1;           /* The error property was already filled. */
    if (available == 0) return 0;           /* Nothing to be read right now.   */

    uint8_t* mem = (uint8_t*)malloc(available);
    if (mem == NULL) {
        m_error = ENOMEM;                   /* No available memory.         */
        return -1;
    }

    available = recv(m_sd, mem, available, 0);
    if (available > 0)
    {
        [buffer appendBytes:mem length:available];
    }
    else if (available == 0)
    {
        m_error = ENOTCONN;                 /* Connection lost.             */

        close(m_sd);                        /* Just in case.                */
        m_sd = -1;
        available = -1;
    }

    free(mem);
    return available;
}
//}}}

// SFStream Support
// - (intptr_t)send:(SFStream *)stream length:(size_t)amount;//{{{
- (intptr_t)send:(SFStream *)stream length:(size_t)amount
{
    if ((stream == nil) || (amount == 0)) {
        m_error = EINVAL;
        return -1;
    }

    size_t size = [stream numberOfBytesAvailable];

    size = ((amount > size) ? size : amount);
    if (size == 0) return 0;

    if (![self send:[stream bytes] ofLength:size])
        return -1;

    [stream setReadPosition:([stream readPosition] + size)];
    return size;
}
//}}}
// - (intptr_t)readIntoStream:(SFStream *)stream;//{{{
- (intptr_t)readIntoStream:(SFStream *)stream
{
    intptr_t available = [self available];
    if (available < 0) return -1;       /* The error property was already filled. */
    if (available == 0) return 0;       /* Idem. */

    void *ptr = [stream bufferWithLength:available];
    if (ptr == NULL) {
        m_error = ENOMEM;
        return -1;
    }

    available = recv(m_sd, ptr, available, 0);
    if (available == 0)
    {
        m_error = ESHUTDOWN;        /* Connection shutdown by the peer. */
        close(m_sd);
        m_sd = -1;
        return -1;
    }
    else if (available < 0)
        m_error = errno;            /* Another kind of error. */
    else
        [stream setWritePosition:([stream writePosition] + available)];

    return available;
}
//}}}

// NSObject: Overrides
// - (id)init;//{{{
- (id)init
{
    self = [super init];
    if (self) m_sd = -1;
    return self;
}
//}}}
// - (void)dealloc;//{{{
- (void)dealloc
{
    if (m_sd >= 0) close(m_sd);
    [super dealloc];
}
//}}}
@end
// vim:syntax=objc.doxygen
