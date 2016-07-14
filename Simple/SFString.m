/**
 * \file
 * Defines the SFString Objective-C category extension for
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
#import "SFString.h"

/* ===========================================================================
 * SFString CATEGORY EXTENSION
 * ======================================================================== */
@implementation NSString (SFString)
// Instance Methods
// - (NSUInteger)uintFromHex:(NSUInteger)defaultValue;//{{{
- (NSUInteger)uintFromHex:(NSUInteger)defaultValue
{
    unsigned int result = 0;
    NSScanner* scanner = [[NSScanner alloc] initWithString:self];

    if (![scanner scanHexInt:&result]) result = (uint)defaultValue;
    [scanner release];
    return result;
}
//}}}
// - (NSString*)stringReplacingEntities;//{{{
- (NSString*)stringReplacingEntities
{
    NSMutableString* string = [NSMutableString stringWithCapacity:([self length] * 4)];

    [string setString:self];

    @try {
        [string replaceOccurrencesOfString:@"&" withString:@"&amp;" options:NSLiteralSearch range:NSMakeRange(0, [string length])];
        [string replaceOccurrencesOfString:@"\"" withString:@"&quot;" options:NSLiteralSearch range:NSMakeRange(0, [string length])];
        [string replaceOccurrencesOfString:@"'" withString:@"&apos;" options:NSLiteralSearch range:NSMakeRange(0, [string length])];
        [string replaceOccurrencesOfString:@"<" withString:@"&lt;" options:NSLiteralSearch range:NSMakeRange(0, [string length])];
        [string replaceOccurrencesOfString:@">" withString:@"&gt;" options:NSLiteralSearch range:NSMakeRange(0, [string length])];
    }
    @catch (NSException* ex) {
        return self;
    }
    return string;
}
//}}}
// - (NSString*)stringRemovingNonDigits;//{{{
- (NSString*)stringRemovingNonDigits
{
    size_t    limit = (size_t)[self length];
    uintptr_t count = 0;
    const char* data = [self cStringUsingEncoding:NSASCIIStringEncoding];
    char* buffer;

    buffer = (char*)malloc(limit*sizeof(char));
    if (!buffer) return nil;

    for (size_t u = 0; u < limit; u++) {
        if (((data[u] < '0') || (data[u] > '9')) &&
            ((data[u] < 'A') || (data[u] > 'F')) &&
            ((data[u] < 'a') || (data[u] > 'f')))
            continue;

        buffer[count++] = data[u];
    }
    buffer[count] = '\0';

    NSString* result = [NSString stringWithCString:buffer encoding:NSASCIIStringEncoding];
    free(buffer);

    return result;
}
//}}}
// - (const char*)utf8Array;//{{{
- (const char*)utf8Array
{
    return [self cStringUsingEncoding:NSUTF8StringEncoding];
}
//}}}
// - (BOOL)isSameAsString:(NSString *)string;//{{{
- (BOOL)isSameAsString:(NSString *)string
{
    return ([self caseInsensitiveCompare:string] == NSOrderedSame);
}
//}}}
// - (BOOL)hasAbsolutePath;//{{{
- (BOOL)hasAbsolutePath
{
    NSArray *array = [self pathComponents];

    if (!array) return NO;
    if ([array count] < 2) return NO;

    NSString *temp = (NSString *)[array objectAtIndex:0];

    return ([temp isSameAsString:@"/"] || [temp isSameAsString:@"~"]);
}
//}}}
// - (BOOL)isEmpty;//{{{
- (BOOL)isEmpty
{
    return ([self length] == 0);
}
//}}}

// Class Methods
// + (NSString*)stringFromBinaryData:(NSData*)data;//{{{
+ (NSString*)stringFromBinaryData:(NSData*)data
{
    size_t count = (data ? [data length] : 0);

    if (count == 0) return [NSString string];

    NSMutableString* buffer = [NSMutableString stringWithCapacity:count * 2];
    const uint8_t*   bytes  = (const uint8_t*)[data bytes];

    for (size_t u = 0; u < count; u++) {
        [buffer appendFormat:@"%02X", bytes[u]];
    }

    return buffer;
}
//}}}
// + (NSUInteger)uintFromText:(NSString*)text onFailure:(NSUInteger)value;//{{{
+ (NSUInteger)uintFromText:(NSString*)text onFailure:(NSUInteger)value
{
    if ((text == nil) || ([text length] == 0)) return value;
    if ([text hasPrefix:@"0x"] || [text hasPrefix:@"0X"])
        return [text uintFromHex:value];

    int result = 0;
    NSScanner* scanner = [[NSScanner alloc] initWithString:text];

    if (![scanner scanInt:&result]) result = (int)value;
    [scanner release];

    return result;
}
//}}}
// + (BOOL)isValid:(NSString*)string;//{{{
+ (BOOL)isValid:(NSString*)string
{
    return ((string != nil) && ![string isEmpty]);
}
//}}}
@end
// vim:syntax=objc.doxygen
