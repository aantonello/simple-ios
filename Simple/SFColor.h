/**
 * \file
 * Declares the SFColor Objective-C category extension for
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
#import <UIKit/UIKit.h>

/**
 * @ingroup sf_categories
 * UIColor Simple additions.
 *//* --------------------------------------------------------------------- */
@interface UIColor (SFColor)
// Class Methods
// + (UIColor*)colorFromRGB:(uint32_t)rgb;//{{{
/**
 * Builds a UIColor object from an RGB color value.
 * \param rgb The RGB color value. This value can be built with the \c RGB()
 * macro.
 * \return A \c UIColor object representing the RGB color value.
 **/
+ (UIColor*)colorFromRGB:(uint32_t)rgb;
//}}}
// + (UIColor*)colorFromARGB:(uint32_t)argb;//{{{
/**
 * Builds a UIColor object from an ARGB color value.
 * \param argb The ARGB color value. This value can be built with the \c
 * ARGB() macro.
 * \return A \c UIColor object representing the ARGB color value.
 **/
+ (UIColor*)colorFromARGB:(uint32_t)argb;
//}}}
@end
// vim:ft=objc syntax=objc.doxygen
