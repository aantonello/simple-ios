/**
 * \file
 * Declares the SFImage Objective-C category extension for
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
#import <UIKit/UIKit.h>

/**
 * @ingroup sf_categories
 * UIImage Simple additions.
 *//* --------------------------------------------------------------------- */
@interface UIImage (SFImage)
/** @name Operations */ //@{
// - (UIImage*)imageWithHorzFixed:(CGFloat)hFixed vertFixed:(CGFloat)vFixed;//{{{
/**
 * Copy the image using a fixed horizontal and vertical measure.
 * The copied image will be resizable in the area not covered by the passed
 * measurement.
 * \param hFixed Pixels that should not be resized in horizontal extent. This
 * measure is used in the left and right sides of the image rectangle.
 * \param vFixed Pixels that should not be resized in vertical extent. This
 * measure is used in the top and bottom sides of the image rectangle.
 * \return A new \c UIImage object that can be resized. The original UIImage
 * object is not changed.
 **/
- (UIImage*)imageWithHorzFixed:(CGFloat)hFixed vertFixed:(CGFloat)vFixed;
//}}}
// - (UIImage*)imageWithInsets:(UIEdgeInsets)edgeInsets;//{{{
/**
 * Copy the image using fixed border extents.
 * The copied image will be resizable in the area not covered by the
 * measurements passed in the \a edgeInsets parameter.
 * \param edgeInsets A \c UIEdgeInsets structure setting the measuremente of
 * the borders that should not be resized with the rest of the image pixel
 * data. This structure object can be built with the function \c
 * UIEdgeInsetsMake().
 * \return A new \c UIImage object that can be resized. The original UIImage
 * object is not changed.
 **/
- (UIImage*)imageWithInsets:(UIEdgeInsets)edgeInsets;
//}}}
//@}
@end
// vim:ft=objc syntax=objc.doxygen
