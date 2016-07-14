/**
 * \file
 * Declares the SFData Objective-C category extension for
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
#import <Foundation/Foundation.h>

/**
 * @ingroup sf_categories
 * NSData Simple additions.
 *//* --------------------------------------------------------------------- */
@interface NSData (SFData)
/** @name Debugging Helpers */ //@{
// - (void)dump:(NSString*)head tail:(NSString*)tail;//{{{
/**
 * Dumps the content of this object to the debugging output system.
 * \param head Text to be written before the data dump. Can be \c NULL.
 * \param tail Text to be written after the data dump. Can be \c NULL.
 **/
- (void)dump:(NSString*)head tail:(NSString*)tail;
//}}}
//@}

// Class Methods
// + (NSData*)dataFromBinaryString:(NSString*)binary;//{{{
/**
 * Creates a NSData object from binary data representation in a string.
 * @param binary A \c NSString object with the binary data representation.
 * @returns An \c NSData object. The resulting object is temporary.
 **/
+ (NSData*)dataFromBinaryString:(NSString*)binary;
//}}}
@end
// vim:ft=objc syntax=objc.doxygen
