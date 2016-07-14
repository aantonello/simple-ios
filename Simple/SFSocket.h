/**
 * \file
 * Declares the SFSocket Objective-C interface class.
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
#import <UIKit/UIKit.h>

/**
 * \defgroup sf_networking Networking
 * Group having Objective-C interface for networking development.
 * @{ *//* ---------------------------------------------------------------- */

/**
 * A Berkley socket implementation in Objective-C.
 *//* --------------------------------------------------------------------- */
@interface SFSocket : NSObject
// Properties
// @property (nonatomic, readonly) error_t error;//{{{
/**
 * Gets the last error number generated from a socket operation.
 **/
@property (nonatomic, readonly) error_t error;
//}}}

/** @name Attributes */ //@{
// - (intptr_t)available;//{{{
/**
 * Gets the amount of data available in the receiving port.
 * \returns The number of data available. Zero is a valid value when there is
 * no data awaiting to be read. A value less than zero means that the socket
 * is in an invalid state. Check the #error property to get the error number.
 **/
- (intptr_t)available;
//}}}
//@}

/** @name Connection */ //@{
// - (error_t)open:(NSString*)address port:(NSUInteger)port;//{{{
/**
 * Starts the connection with the peer.
 * This operation only starts the connection job. The operaion will be
 * completed in background.
 * \param address NSString with the peer address. Can be an IP or URI.
 * \param port Connection port number.
 * \return The result is an error code. When this value is 0 then the
 * connection is ready. When this value is \c EINPROGRESS the connection will
 * be completed in background. Any other value is an error code and the
 * connection could not be made.
 **/
- (error_t)open:(NSString*)address port:(NSUInteger)port;
//}}}
// - (error_t)isReady;//{{{
/**
 * Checks if the connection was made.
 * \returns The type of result is an error number with the possible meanings:
 * - 0 (zero): Means success. The connection is bound and ready.
 * - EINPROGRESS: The connection is still in progress.
 * - Any other value: Is an error number that ends the current connection
 * operation. This is the failure reason.
 * .
 * \remarks The returned value also can be recovered by #error property.
 **/
- (error_t)isReady;
//}}}
//@}

/** @name Communication */ //@{
// - (BOOL)send:(NSData*)data;//{{{
/**
 * Sends data to the connected peer.
 * \param data The data to be send.
 * \return \b YES if the data was sent. \b NO when an error occurs. The check
 * the error code see the #error property.
 **/
- (BOOL)send:(NSData*)data;
//}}}
// - (BOOL)send:(const void*)data ofLength:(size_t)length;//{{{
/**
 * Sends data to the connected peer.
 * \param data Pointer to the address of the data.
 * \param length Length of the data to send, in bytes.
 * \return \b YES if the data was sent. \b NO when an error occurs. The check
 * the error code see the #error property.
 **/
- (BOOL)send:(const void*)data ofLength:(size_t)length;
//}}}
// - (intptr_t)read:(void*)buffer ofLength:(size_t)size;//{{{
/**
 * Reads the available data into the specified buffer.
 * \param buffer Address of memory to store the read data.
 * \param size Length of available memory in \a buffer.
 * \return The function returns the length of data actualy read and copied
 * into the \a buffer memory location. This can be less than the passed in \a
 * size argument. You must always check the length of the data available
 * first, and try to read all that data once. If there is more data than the
 * length of the passed \a buffer, the data will be truncated.
 *
 * When there is no data to be read the function returns 0 (zero). If an error
 * occurs the function returns -1. The error code can be recovered using the
 * #error property.
 **/
- (intptr_t)read:(void*)buffer ofLength:(size_t)size;
//}}}
// - (intptr_t)read:(NSMutableData*)buffer;//{{{
/**
 * Read the available data in the socket port.
 * \param buffer NSMutableData where the data will be read and returned.
 * \return The function returns the length of data actualy read and copied
 * into the \a buffer object.
 *
 * When there is no data to be read the function returns 0 (zero). If an error
 * occurs the function returns -1. The error code can be recovered using the
 * #error property.
 **/
- (intptr_t)read:(NSMutableData*)buffer;
//}}}
//@}

/** @name SFStream Support */ //@{
// - (intptr_t)send:(SFStream *)stream length:(size_t)amount;//{{{
/**
 * Sends data read from a SFStream object.
 * @param stream SFStream object with data to send. This object will be read
 * starting from its read position.
 * @param amount Total number of bytes to send. This can be \c UINTPTR_MAX to
 * send all data, starting from the stream current reading position, to the
 * connected peer. If this value is zero, the function does nothing.
 * @return The total number of byte sent means success. When the function
 * returns a value less than zero an error occurred. The error can be
 * retrieved by the #error property. If \a stream was \b nil or \a amount was
 * zero, the result will be \c EINVAL. If \a stream is empty the function
 * returns 0, which is a valid value and doesn't mean an error.
 * @remarks If the operation fails in any way the \a stream reading position
 * will not be changed.
 **/
- (intptr_t)send:(SFStream *)stream length:(size_t)amount;
//}}}
// - (intptr_t)readIntoStream:(SFStream *)stream;//{{{
/**
 * Reads data from the communication port and writes it in the passed stream.
 * @param stream SFStream where the read data will be stored. Must not be \b
 * nil.
 * @return A value greater than or equals to 0 means success, representing the
 * total number of bytes read. Zero means that was no available data to be
 * read. When an error occurs, like when the connection was lost, the result
 * will be less than zero and the error condition can be retrieved by the
 * #error property.
 * @remarks The current write position is taken into account to write the data
 * in the passed stream. Memory is automaticaly allocated as needed. If the
 * function fails, nothing is written and, by so, the write position is not
 * changed.
 **/
- (intptr_t)readIntoStream:(SFStream *)stream;
//}}}
//@}
@end
///@} sf_networking
// vim:ft=objc syntax=objc.doxygen
