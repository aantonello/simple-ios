/**
 * \file
 * Defines the SFDictionary Objective-C category extension for
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
#include <stdlib.h>
#include <unistd.h>

#import <CoreGraphics/CGGeometry.h>
#import "SFDictionary.h"
#import "SFString.h"

/* ===========================================================================
 * SFDictionary CATEGORY EXTENSION
 * ======================================================================== */
@implementation NSDictionary (SFDictionary)
// Values Retrieving and Converting
// - (intptr_t)integerValueForKey:(NSString *)key usingDefault:(intptr_t)defaultValue;//{{{
- (intptr_t)integerValueForKey:(NSString *)key usingDefault:(intptr_t)defaultValue
{
    NSString *value = (NSString *)[self valueForKey:key];

    if ((!value) || ([value length] == 0))
        return defaultValue;

    char *tail = NULL;
    const char *ptr = [value utf8Array];
    intptr_t result;

    errno = 0;
    result = strtol(ptr, &tail, 0);
    if ((tail != NULL) && ((*tail) != '\0') && (errno != 0))
        return defaultValue;

    return result;
}
//}}}
// - (uintptr_t)unsignedValueForKey:(NSString *)key usingDefault:(uintptr_t)defaultValue;//{{{
- (uintptr_t)unsignedValueForKey:(NSString *)key usingDefault:(uintptr_t)defaultValue
{
    return (uintptr_t)[self integerValueForKey:key usingDefault:defaultValue];
}
//}}}
// - (CGFloat)floatValueForKey:(NSString *)key usingDefault:(CGFloat)floatValue;//{{{
- (CGFloat)floatValueForKey:(NSString *)key usingDefault:(CGFloat)floatValue
{
    NSString *value = (NSString *)[self valueForKey:key];

    if ((!value) || ([value length] == 0))
        return floatValue;

    return [value floatValue];
}
//}}}
@end

/* ===========================================================================
 * SFMutableDictionary CATEGORY EXTENSION
 * ======================================================================== */
@implementation NSMutableDictionary (SFMutableDictionary)
// Defining Values
// - (void)integerValue:(intptr_t)value forKey:(NSString *)key;//{{{
- (void)integerValue:(intptr_t)value forKey:(NSString *)key
{
    NSString *newValue = [NSString stringWithFormat:@"%ld", value];
    [self setValue:newValue forKey:key];
}
//}}}
// - (void)unsignedValue:(uintptr_t)value forKey:(NSString *)key;//{{{
- (void)unsignedValue:(uintptr_t)value forKey:(NSString *)key
{
    NSString *newValue = [NSString stringWithFormat:@"%lu", value];
    [self setValue:newValue forKey:key];
}
//}}}
// - (void)floatValue:(float)value forKey:(NSString *)key;//{{{
- (void)floatValue:(CGFloat)value forKey:(NSString *)key
{
    NSString *newValue = [NSString stringWithFormat:@"%01.6f", value];
    [self setValue:newValue forKey:key];
}
//}}}
@end
// vim:syntax=objc.doxygen
