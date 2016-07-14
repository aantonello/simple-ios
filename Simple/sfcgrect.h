/**
 * @file
 * Functions and macros to work with CGRect structure.
 *
 * @author Alessandro Antonello aantonello@paralaxe.com.br
 * @date   February 04, 2015
 * @since  Simple Framework 1.3
 *
 * \copyright
 * This file is provided in hope that it will be useful to someone. It is
 * offered in public domain. You may use, modify or distribute it freely.
 *
 * The code is provided "AS IS". There is no warranty at all, of any kind. You
 * may change it if you like. Or just use it as it is.
 */
#import <Foundation/Foundation.h>
#import <CoreGraphics/CGGeometry.h>

/**
 * @ingroup sf_general
 * @defgroup sf_general_geometry Geometry
 * Functions and macros to work with CGRect, CGPoint and CGSize structures.
 * This set of operations are similar to those provided by the \c rect_t
 * structure and \c SFRect interface. But, in this group, they work directly
 * in the standard iOS/OS X structures.
 *
 * To not colide with functions and macros defined for \c rect_t and \c SFRect
 * types those defined here are prefixed with "cgrect_" string.
 * @since 1.3
 */

// #define cgrect_x(r)         ((r).origin.x)//{{{
/**
 * @ingroup sf_general_geometry
 * Gets or sets the minimal X coordinate of a CGRect structure.
 * @param r A CGRect structure.
 * @returns The horizontal coordinate of the rectangle.
 * @remarks This function-macro can be used both to get and set the horizontal
 * coordinate of the rectangle.
 * ~~~~~~~~~~~~~~~~~~{.m}
 * CGFloat x = cgrect_x(rect);      // Gets the x coordinate.
 * cgrect_x(rect) = x;              // Sets the x coordinate.
 * ~~~~~~~~~~~~~~~~~~
 * @note The CGRect structure must be normalized.
 * @since 1.3
 **/
#define cgrect_x(r)         ((r).origin.x)
//}}}
// #define cgrect_y(r)         ((r).origin.y)//{{{
/**
 * @ingroup sf_general_geometry
 * Gets or sets the minimal Y coordinate of a CGRect structure.
 * @param r A CGRect structure.
 * @returns The vertical coordinate of the rectangle.
 * @remarks This function-macro can be used both to get and set the vertical
 * coordinate of the rectangle.
 * ~~~~~~~~~~~~~~~~~~{.m}
 * CGFloat y = cgrect_y(rect);      // Gets the y coordinate.
 * cgrect_y(rect) = y;              // Sets the y coordinate.
 * ~~~~~~~~~~~~~~~~~~
 * @note The CGRect structure must be normalized.
 * @since 1.3
 **/
#define cgrect_y(r)         ((r).origin.y)
//}}}
// #define cgrect_width(r)     ((r).size.width)//{{{
/**
 * @ingroup sf_general_geometry
 * Gets or sets the width of the rectangle.
 * @param r A CGRect structure.
 * @returns The width of the rectangle.
 * @remarks This function-macro can be used both to get or set the width of
 * the rectangle structure.
 * ~~~~~~~~~~~~~~~~~~{.m}
 * CGFloat width = cgrect_width(rect);      // Gets the width.
 * cgrect_width(rect) = width;              // Sets the width.
 * ~~~~~~~~~~~~~~~~~~
 * @note The CGRect structure must be normalized.
 * @since 1.3
 **/
#define cgrect_width(r)     ((r).size.width)
//}}}
// #define cgrect_height(r)    ((r).size.height)//{{{
/**
 * @ingroup sf_general_geometry
 * Gets or sets the height of the rectangle.
 * @param r A CGRect structure.
 * @returns The height of the rectangle.
 * @remarks This function-macro can be used both to get or set the height of
 * the rectangle structure.
 * ~~~~~~~~~~~~~~~~~~{.m}
 * CGFloat height = cgrect_height(rect);      // Gets the height.
 * cgrect_height(rect) = height;              // Sets the height.
 * ~~~~~~~~~~~~~~~~~~
 * @note The CGRect structure must be normalized.
 * @since 1.3
 **/
#define cgrect_height(r)    ((r).size.height)
//}}}

// #define cgrect_right(r)     (cgrect_x(r) + cgrect_width(r))//{{{
/**
 * @ingroup sf_general_geometry
 * Returns the right coordinate of the rectangle.
 * @param r A CGRect structure.
 * @returns The right most horizontal coordinate of the rectangle.
 * @remarks To change the right most coordinate of the rectangle see 
 * cgrect_inflate(), cgrect_align() or cgrect_right_at().
 * @note The CGRect structure must be normalized.
 * @since 1.3
 **/
#define cgrect_right(r)     (cgrect_x(r) + cgrect_width(r))
//}}}
// #define cgrect_bottom(r)    (cgrect_y(r) + cgrect_height(r))//{{{
/**
 * @ingroup sf_general_geometry
 * Gets the bottom coordinate of the rectangle.
 * @param r A CGRect structure.
 * @returns The bottom most vertical coordinate of the rectangle.
 * @remarks To change the bottom most coordinate of the rectangle see 
 * cgrect_inflate(), cgrect_align() or cgrect_bottom_at().
 * @note The CGRect structure must be normalized.
 * @since 1.3
 **/
#define cgrect_bottom(r)    (cgrect_y(r) + cgrect_height(r))
//}}}
// #define cgrect_start(r)     CGPointMake(cgrect_x(r), cgrect_y(r))//{{{
/**
 * @ingroup sf_general_geometry
 * Build a CGPoint structure based on the origin coordinate of the given
 * rectangle.
 * @param r A CGRect structure.
 * @return A CGPoint structure. This is a new structure, not the structure
 * that builds the CGRect parameter.
 * @remarks To change the starting point of the rectangle in one operation see
 * \c cgrect_offset().
 * @note The CGRect structure must be normalized.
 * @since 1.3
 **/
#define cgrect_start(r)     CGPointMake(cgrect_x(r), cgrect_y(r))
//}}}
// #define cgrect_end(r)       CGPointMake(cgrect_right(r), cgrect_bottom(r))//{{{
/**
 * @ingroup sf_general_geometry
 * Builds a CGPoint structure with the ending coordinates of the rectangle.
 * @param r A CGRect structure.
 * @returns A CGPoint structure built with the right most and bottom most
 * coordinates of the rectangle parameter.
 * @remarks To change the end point of the rectangle, moving or resinzing it,
 * see \c cgrect_align().
 * @note The CGRect structure must be normalized.
 * @since 1.3
 **/
#define cgrect_end(r)       CGPointMake(cgrect_right(r), cgrect_bottom(r))
//}}}
// #define cgrect_center(r)    CGPointMake(cgrect_x(r) + (cgrect_width(r) / 2), cgrect_y(r) + (cgrect_height(r) / 2))//{{{
/**
 * @ingroup sf_general_geometry
 * Build a CGPoint structure pointing to the coordinates of the center of the
 * rectangle.
 * @param r A CGRect structure.
 * @returns A CGPoint structure having the coordinates of the center of the
 * rectangle.
 * @remarks To centralize the rectangle in an specified point see \c
 * cgrect_centralize() or \c cgrect_align().
 * @note The CGRect structure must be normalized.
 * @since 1.3
 **/
#define cgrect_center(r)    CGPointMake(cgrect_x(r) + (cgrect_width(r) / 2), cgrect_y(r) + (cgrect_height(r) / 2))
//}}}
// #define cgrect_empty(r)     ((cgrect_width(r) <= 0) || (cgrect_height(r) <= 0))//{{{
/**
 * @ingroup sf_general_geometry
 * Checks whether the given \c CGRect structure has empty coordinates.
 * @param r A CGRect structure.
 * @returns \b TRUE when the rectangle is empty. \b FALSE otherwise.
 * @remarks A rectangle is empty when its width or height is less than or
 * equals to zero. Same as \c CGRectIsEmpty().
 * @note The CGRect structure must be normalized.
 * @since 1.3
 **/
#define cgrect_empty(r)     ((cgrect_width(r) <= 0) || (cgrect_height(r) <= 0))
//}}}

// #define cgrect_offset(r, dx, dy)    (cgrect_x(r) += (dx)), (cgrect_y(r) += (dy))//{{{
/**
 * @ingroup sf_general_geometry
 * Moves the rectangle by an offset.
 * @param r A CGRect structure.
 * @param dx Offset to be added to the horizontal coordinate. If this value is
 * positive the rectangle will be moved to the right. If this value is
 * negative the rectangle will be moved to the left. As of this is a macro
 * function this parameter can be any integral type. It will be cast to a \c
 * CGFloat in the operation.
 * @param dy Offset to be added to the vertical coordinate. If this value is
 * positive the rectangle will be moved toward bottom. If this value is
 * negative the rectangle will be moved toward top. As of this is a macro
 * function this parameter can be any integral type. It will be cast to a \c
 * CGFloat in the operation.
 * @return The result is the vertical coordinate of the rectangle after the
 * change is made. The difference from the \c CGRectOffset() function is that
 * the change is made in the source rectangle. No new \c CGRect object is
 * created.
 * @remarks The operation is done with two instructions separated by a comma
 * operator, allowing this macro to be used inside an instruction block
 * without be enclosed in curli braces.
 * @since 1.3
 **/
#define cgrect_offset(r, dx, dy)    (cgrect_x(r) += ((CGFloat)(dx))), (cgrect_y(r) += ((CGFloat)(dy)))
//}}}
// #define cgrect_right_at(r, x)       cgrect_x(r) = (((CGFloat)(x)) - cgrect_width(r))//{{{
/**
 * @ingroup sf_general_geometry
 * Offsets the rectangle's horizontal coordinate so that it's right coordinate
 * will be equals to the passed value.
 * @param r A CGRect structure.
 * @param x The horizontal coordinate to align the rectangle.
 * @returns The resulting value will be the left coordinate of the rectangle
 * after the change is made.
 * @remarks The change is made in place as of this is a function macro.
 * @note The CGRect structure must be normalized.
 * @since 1.3
 **/
#define cgrect_right_at(r, x)       cgrect_x(r) = (((CGFloat)(x)) - cgrect_width(r))
//}}}
// #define cgrect_bottom_at(r, y)      cgrect_y(r) = (((CGFloat)(y)) - cgrect_height(r))//{{{
/**
 * @ingroup sf_general_geometry
 * Offsets the rectangle's vertical coordinate so that it's bottom coordinate
 * will be equals to the passed value.
 * @param r A CGRect structure.
 * @param y The vertical coordinate to align the rectangle.
 * @returns The resulting value will be the vertical coordinate of the rectangle
 * after the change is made.
 * @remarks The change is made in place as of this is a function macro.
 * @note The CGRect structure must be normalized.
 * @since 1.3
 **/
#define cgrect_bottom_at(r, y)      cgrect_y(r) = (((CGFloat)(y)) - cgrect_height(r))
//}}}

// CGRect cgrect_inflate(CGRect source, CGFloat dx, CGFloat dy, CGFloat rx, CGFloat ry);//{{{
/**
 * @ingroup sf_general_geometry
 * Inflates or deflates a rectangle.
 * @param source The original rectangle structure.
 * @param dx Value to be subtracted from the left most rectangle coordinate
 * (origin 'x').
 * @param dy Value to be subtracted from the top most rectangle coordinate
 * (origin 'y').
 * @param rx Value to be added to the rigth most rectangle coordinate.
 * @param ry Value to be added to the bottom most rectangle coordinate.
 * @returns A new \c CGRect structure made by the changes defined. The
 * original \p source rectangle will not be modified.
 * @remarks This function changes the rectangle's coordinates separately. Each
 * parameter is treated as an offset and changes the specified single
 * coordinate. As this function \e inflates the rectangle the first two
 * parameters (\p dx and \p dy) are used to change the origin x and origin
 * y coordinates by subtracting the values passed in. The values passed in the
 * two final parameters (\p rx and \p ry) will be added to the width and
 * height values of the rectangle ajusted to by the values passed in the two
 * first parameters. If you need to inset (deflate) the rectangle you can pass
 * negative values in the final for parameters.
 *
 * If you are looking for a way to inflate or deflate a \c CGRect by its
 * center take a look at the \c CGRectInset() function.
 * @since 1.3
 **/
CGRect cgrect_inflate(CGRect source, CGFloat dx, CGFloat dy, CGFloat rx, CGFloat ry);
//}}}
// CGRect cgrect_align(CGRect source, int align, CGRect reference);//{{{
/**
 * @ingroup sf_general_geometry
 * Aligns the source rectangle taking another rectangle as reference.
 * @param source The source \c CGRect structure to be aligned.
 * @param align Set of flags specifying how the \p source rectangle should be
 * aligned. Valid values are those listed in the SFRectAlign enumeration.
 * Values may be combined using the or (|) operator. Not all flags can be
 * combined successfuly. For example, combining \c SFRectAlignLeft with \c
 * SFRectAlignAtLeft doesn't make sence. The behavior of the function will be
 * to use the \c SFRectAlignAtLeft and forget about the first.
 * @param reference The reference \c CGRect structure with the coordinates
 * used to align the \p source rectangle.
 * @returns A new \c CGRect structure built with coordinates to correctly
 * align the \p source rectangle by the \p reference rectangle. The \p source
 * \c CGRect structure will not be modified by this function.
 * @note The CGRect structure must be normalized.
 * @since 1.3
 **/
CGRect cgrect_align(CGRect source, int align, CGRect reference);
//}}}
// CGRect cgrect_fit(CGRect source, int flags, CGRect reference);//{{{
/**
 * @ingroup sf_general_geometry
 * Resize the source rectangle so it fits inside the reference rectangle.
 * @param source The source \c CGRect structure to be resized.
 * @param flags Set of flags defining how the function will operate. Can be
 * any value defined in the SFRectStretch enumeration.
 * @param reference The reference \c CGRect structure with the coordinates
 * used to resize the \p source rectangle.
 * @returns A new \c CGRect structure with its size correctly changed to fit
 * the sizes of the \p reference rectangle. The \p source \c CGRect structure
 * will not be modified by this function.
 * @note The CGRect structure must be normalized.
 * @since 1.3
 **/
CGRect cgrect_fit(CGRect source, int flags, CGRect reference);
//}}}
// CGRect cgrect_centralize(CGRect source, CGPoint center);//{{{
/**
 * @ingroup sf_general_geometry
 * Centralizes a rectangle in the giving point.
 * @param source A CGRect structure.
 * @param center A CGPoint structure defining the centralization coordinates.
 * @return A new \c CGRect structure with the same width and height of the \p
 * source parameter but with its x and y coordinates changed so that its
 * center matches the \p center parameter.
 * @note The CGRect structure must be normalized.
 * @since 1.3
 **/
CGRect cgrect_centralize(CGRect source, CGPoint center);
//}}}

