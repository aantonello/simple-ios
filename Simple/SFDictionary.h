/**
 * \file
 * Declares the SFDictionary Objective-C category extension for
 * NSDictionary interface.
 *
 * \author  Alessandro Antonello aantonello@paralaxe.com.br
 * \date    April 28, 2014
 * \since   Simple Framework 1.2
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
 * NSDictionary new messages.
 *//* --------------------------------------------------------------------- */
@interface NSDictionary (SFDictionary)
/** @name Values Retrieving and Converting */ //@{
// - (intptr_t)integerValueForKey:(NSString *)key usingDefault:(intptr_t)defaultValue;//{{{
/**
 * Converts an entry to a signed integer value.
 * @param key Key entry name.
 * @param defaultValue Value that will be used if the entry name does not
 * exists or cannot be converted to a signed integer value.
 * @return The value of the key, converted to a signed integer value or the \a
 * defaultValue if the conversion fails.
 * @remarks The conversion is done using \c strtol() standard C function.
 * There is no assunption if the number is stored in decimal, hexadecimal or
 * octal format. The operation will try all formats before failing.
 **/
- (intptr_t)integerValueForKey:(NSString *)key usingDefault:(intptr_t)defaultValue;
//}}}
// - (uintptr_t)unsignedValueForKey:(NSString *)key usingDefault:(uintptr_t)defaultValue;//{{{
/**
 * Converts an entry to an unsigned integer value.
 * @param key Key entry name.
 * @param defaultValue Value that will be used if the entry name does not
 * exists or cannot be converted to an unsigned integer value.
 * @return The value of the key, converted to an unsigned integer value or the
 * \a defaultValue if the conversion fails.
 * @remarks The conversion is done using \c strtol() standard C function.
 * There is no assunption if the number is stored in decimal, hexadecimal or
 * octal format. The operation will try all formats before failing.
 **/
- (uintptr_t)unsignedValueForKey:(NSString *)key usingDefault:(uintptr_t)defaultValue;
//}}}
// - (CGFloat)floatValueForKey:(NSString *)key usingDefault:(CGFloat)floatValue;//{{{
/**
 * Converts an entry to a floating point number.
 * @param key Key entry name.
 * @param floatValue Value that will be used if the entry name does not
 * exists or cannot be converted to floating point number.
 * @return The value of the key, converted to floating point number or the
 * \a floatValue if the conversion fails.
 * @remarks The conversion is done using \c NSString::floatValue operation.
 **/
- (CGFloat)floatValueForKey:(NSString *)key usingDefault:(CGFloat)floatValue;
//}}}
//@}
@end

/**
 * @ingroup sf_categories
 * NSMutableDictionary extension.
 *//* --------------------------------------------------------------------- */
@interface NSMutableDictionary (SFMutableDictionary)
/** @name Defining Values */ //@{
// - (void)integerValue:(intptr_t)value forKey:(NSString *)key;//{{{
/**
 * Sets a signed integer value for a key.
 * @param value The signed integer value.
 * @param key The key to add or change.
 * @remarks The value is written in decimal notaion.
 **/
- (void)integerValue:(intptr_t)value forKey:(NSString *)key;
//}}}
// - (void)unsignedValue:(uintptr_t)value forKey:(NSString *)key;//{{{
/**
 * Sets an unsigned integer value to a key.
 * @param value The unsigned integer value.
 * @param key The key to add or change.
 * @remarks The value is written in decimal notaion.
 **/
- (void)unsignedValue:(uintptr_t)value forKey:(NSString *)key;
//}}}
// - (void)floatValue:(CGFloat)value forKey:(NSString *)key;//{{{
/**
 * Sets a floating point number to a key.
 * @param value The floating point number.
 * @param key The key to add or change.
 **/
- (void)floatValue:(CGFloat)value forKey:(NSString *)key;
//}}}
//@}
@end
// vim:ft=objc syntax=objc.doxygen
