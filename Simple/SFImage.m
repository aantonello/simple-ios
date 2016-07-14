/**
 * \file
 * Defines the SFImage Objective-C category extension for
 * UIImage interface.
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
#import "SFImage.h"

/* ===========================================================================
 * SFImage CATEGORY EXTENSION
 * ======================================================================== */
@implementation UIImage (SFImage)
// Operations
// - (UIImage*)imageWithHorzFixed:(CGFloat)hFixed vertFixed:(CGFloat)vFixed;//{{{
- (UIImage*)imageWithHorzFixed:(CGFloat)hFixed vertFixed:(CGFloat)vFixed
{
    return [self resizableImageWithCapInsets:UIEdgeInsetsMake(vFixed, hFixed, vFixed, hFixed)];
}
//}}}
// - (UIImage*)imageWithInsets:(UIEdgeInsets)edgeInsets;//{{{
- (UIImage*)imageWithInsets:(UIEdgeInsets)edgeInsets
{
    return [self resizableImageWithCapInsets:edgeInsets];
}
//}}}
@end
// vim:syntax=objc.doxygen
