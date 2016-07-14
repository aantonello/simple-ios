/**
 * \file
 * Declares the SFString Objective-C category extension for
 * NSString interface.
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
 * NSString Simple additions.
 *//* --------------------------------------------------------------------- */
@interface NSString (SFString)
/** @name Operations */ //@{
// - (NSUInteger)uintFromHex:(NSUInteger)defaultValue;//{{{
/**
 * Scans this string content to convert it in an unsigned integer number.
 * \param defaultValue Value to be returned when this string doesn't have a
 * valid unsigned integer number.
 **/
- (NSUInteger)uintFromHex:(NSUInteger)defaultValue;
//}}}
// - (NSString*)stringReplacingEntities;//{{{
/**
 * Replace all special XML characters with corresponding entities.
 * The function will not operate in the content of this string object. Instead
 * it will build a copy of it, replacing all special characters.
 * @return A new string instance built of a copy of this object.
 **/
- (NSString*)stringReplacingEntities;
//}}}
// - (NSString*)stringRemovingNonDigits;//{{{
/**
 * Copy this string removing any non-digit character.
 * @return The result is a copy of the content of this string without any
 * non-digit charater. If no digit character remains on string, the result
 * will be an empty string.
 **/
- (NSString*)stringRemovingNonDigits;
//}}}
// - (const char*)utf8Array;//{{{
/**
 * Converts the contents of this object to a \c char array.
 * The conversion will be using the UTF-8 string enconding.
 * \return A \c char array with the converted string. Can be \b NULL, if the
 * content of this string could not be converted.
 * \remarks The result string is managed internally by this object. It should
 * NOT be freed. It will remain available as of this object instance is
 * available.
 **/
- (const char*)utf8Array;
//}}}
// - (BOOL)isSameAsString:(NSString *)string;//{{{
/**
 * Compares two strings ignoring case.
 * @param string NSString to compare with this instance.
 * @return \b YES when the two strings are equal ignoring case. \b NO
 * otherwise.
 **/
- (BOOL)isSameAsString:(NSString *)string;
//}}}
// - (BOOL)hasAbsolutePath;//{{{
/**
 * Checks whether the contents of this string has an absolute path
 * information.
 * @return \b YES if this string has an absolute path information. Otherwise
 * \b NO.
 * @since 1.3
 **/
- (BOOL)hasAbsolutePath;
//}}}
// - (BOOL)isEmpty;//{{{
/**
 * Checks whether this strings instance is empty.
 * The string is empty when it has a zero length string data.
 * @returns \b YES when the string is empty. Otherwise, \b NO.
 * @since 1.3
 **/
- (BOOL)isEmpty;
//}}}
//@}

// Class Methods
// + (NSString*)stringFromBinaryData:(NSData*)data;//{{{
/**
 * Builds a new \c NSString object based on the data passed.
 * The resulting string will have the content of the \a data object converted
 * to text. That is, each byte will be converted to a two character long,
 * hexadecimal representation of the byte value.
 * @param data \c NSData object with the binary data to be parsed.
 * @return A \c NSString object with the parsed data.
 **/
+ (NSString*)stringFromBinaryData:(NSData*)data;
//}}}
// + (NSUInteger)uintFromText:(NSString*)text onFailure:(NSUInteger)value;//{{{
/**
 * Parses a string and returs a unsigned integer value.
 * \param text String to parse. Can have a signaled value, an unsignaled
 * value or hexadecimal value. Can even be \c nil.
 * \param value Default value to return if the conversion fails.
 * \return The number found or the value of \a value, if the conversion fails.
 * The result will always be unsignaled but you can cast it to a signaled
 * value.
 **/
+ (NSUInteger)uintFromText:(NSString*)text onFailure:(NSUInteger)value;
//}}}
// + (BOOL)isValid:(NSString*)string;//{{{
/**
 * Checks whether an \c NSString instance is not empty nor \b nil.
 * @param string The object instance to be checked.
 * @returns \b YES when the passed object reference is not \b nil nor is an
 * empty string. Otherwise \b NO.
 * @since 1.3
 **/
+ (BOOL)isValid:(NSString*)string;
//}}}
@end
// vim:ft=objc syntax=objc.doxygen
