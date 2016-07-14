/**
 * @file
 * Implements the SFDeviceInfo interface class.
 *
 * @author Alessandro Antonello aantonello@paralaxe.com.br
 * @date   February 05, 2015
 * @since  Simple Framework 1.3
 *
 * \copyright
 * This file is provided in hope that it will be useful to someone. It is
 * offered in public domain. You may use, modify or distribute it freely.
 *
 * The code is provided "AS IS". There is no warranty at all, of any kind. You
 * may change it if you like. Or just use it as it is.
 */
#import <UIKit/UIKit.h>
#import "SFDeviceInfo.h"

/* ===========================================================================
 * SFDeviceInfo Implementation
 * ======================================================================== */

/* ---------------------------------------------------------------------------
 * Implementation
 * ------------------------------------------------------------------------ */
@implementation SFDeviceInfo
// Device Information
// + (NSString *)deviceName;//{{{
+ (NSString *)deviceName
{
    return [[UIDevice currentDevice] name];
}
//}}}
// + (NSString *)deviceModel;//{{{
+ (NSString *)deviceModel
{
    return [[UIDevice currentDevice] model];
}
//}}}
// + (NSString *)systemName;//{{{
+ (NSString *)systemName
{
    return [[UIDevice currentDevice] systemName];
}
//}}}
// + (NSString *)systemVersion://{{{
+ (NSString *)systemVersion
{
    return [[UIDevice currentDevice] systemVersion];
}
//}}}
// + (BOOL)deviceIsTablet;//{{{
+ (BOOL)deviceIsTablet
{
    return ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPad);
}
//}}}
// + (BOOL)deviceIsPhone;//{{{
+ (BOOL)deviceIsPhone
{
    return ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone);
}
//}}}

// Main Screen Information
// + (CGRect)screenBounds;//{{{
+ (CGRect)screenBounds
{
    return [[UIScreen mainScreen] bounds];
}
//}}}
// + (CGRect)applicationFrame;//{{{
+ (CGRect)applicationFrame
{
    return [[UIScreen mainScreen] bounds];
}
//}}}
// + (CGFloat)screenScale;//{{{
+ (CGFloat)screenScale
{
    return [[UIScreen mainScreen] scale];
}
//}}}
// + (CGFloat)aspectRatio;//{{{
+ (CGFloat)aspectRatio
{
    return [[[UIScreen mainScreen] currentMode] pixelAspectRatio];
}
//}}}
@end
