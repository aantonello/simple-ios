/**
 * \file
 * Defines the SFColor Objective-C category extension for
 * UIColor interface.
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
#import "SFColor.h"
#import "sfstd.h"

/* ===========================================================================
 * SFColor CATEGORY EXTENSION
 * ======================================================================== */
@implementation UIColor (SFColor)
// Class Methods
// + (UIColor*)colorFromRGB:(uint32_t)rgb;//{{{
+ (UIColor*)colorFromRGB:(uint32_t)rgb
{
    return [UIColor colorWithRed:RED_F(rgb) green:GREEN_F(rgb) blue:BLUE_F(rgb) alpha:1.0];
}
//}}}
// + (UIColor*)colorFromARGB:(uint32_t)argb;//{{{
+ (UIColor*)colorFromARGB:(uint32_t)argb
{
    return [UIColor colorWithRed:RED_F(argb) green:GREEN_F(argb) blue:BLUE_F(argb) alpha:ALPHA_F(argb)];
}
//}}}
@end
// vim:syntax=objc.doxygen
