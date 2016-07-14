/**
 * \file
 * Defines the SFData Objective-C category extension for
 * NSData interface.
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
#import "SFData.h"
#import "SFString.h"
#import "sfdebug.h"

/* ===========================================================================
 * SFData CATEGORY EXTENSION
 * ======================================================================== */
@implementation NSData (SFData)
// Debugging Helpers
// - (void)dump:(NSString*)head tail:(NSString*)tail;//{{{
- (void)dump:(NSString*)head tail:(NSString*)tail
{
#ifdef DEBUG
    const char* header = (head ? [head utf8Array] : NULL);
    const char* footer = (tail ? [tail utf8Array] : NULL);

    sfflush(header, [self bytes], [self length], footer);
#else
#pragma unused(head)
#pragma unused(tail)
#endif
}
//}}}

// Class Methods
// + (NSData*)dataFromBinaryString:(NSString*)binary;//{{{
+ (NSData*)dataFromBinaryString:(NSString*)binary
{
    const char* data = [binary cStringUsingEncoding:NSASCIIStringEncoding];
    size_t     limit = (size_t)[binary length];
    uint8_t  *buffer, *ptr;
    uint32_t    temp;

    buffer = (uint8_t*)malloc(limit/2);
    if (!buffer) return nil;
    memset(buffer, 0, (limit/2));

    ptr = buffer;
    while (*data)
    {
        if (*data >= 'a')
            temp = *data - 'a' + 10;
        else if (*data >= 'A')
            temp = *data - 'A' + 10;
        else
            temp = *data - '0';

        temp *= 16; data++;

        if (*data >= 'a')
            temp += *data - 'a' + 10;
        else if (*data >= 'A')
            temp += *data - 'A' + 10;
        else
            temp += *data - '0';

        *ptr++ = (uint8_t)temp;
        data++;
    }

    NSData* result = [NSData dataWithBytes:buffer length:(limit/2)];
    free(buffer);

    return result;
}
//}}}
@end
// vim:syntax=objc.doxygen
