/**
 * \file
 * Standard macros and defines.
 *
 * \author Alessandro Antonello aantonello@paralaxe.com.br
 * \date   March 14, 2013
 *
 * \copyright
 * This file is provided in hope that it will be useful to someone. It is
 * offered in public domain. You may use, modify or distribute it freely.
 *
 * The code is provided "AS IS". There is no warranty at all, of any kind. You
 * may change it if you like. Or just use it as it is.
 */
#ifndef __SFSTD_H_DEFINED__
#define __SFSTD_H_DEFINED__

/**
 * \defgroup sf_general General
 * Module containing general macros, constants and interfaces.
 * @{ *//* ---------------------------------------------------------------- */
#ifndef TRUE
#  define TRUE 1                        /**< Same as 'YES'. */
#endif

#ifndef FALSE
#  define FALSE 0                       /**< Same as 'NO'. */
#endif

#ifndef __error_t_defined
typedef int     error_t;                /**< Type for error values. */
#define __error_t_defined 1
#endif

#ifndef __socket_t_defined
typedef int         socket_t;           /**< Type for socket descriptors. */
#define __socket_t_defined 1
#endif

#ifndef CONSTRAINT
/**
 * Keep a value in between some range.
 * @param v The value to check.
 * @param _min The minimum value.
 * @param _max The maximum value.
 * @return @a v, @a _min or @a _max.
 **/
#  define CONSTRAINT(v, _min, _max)     ((v < _min) ? _min : ((v > _max) ? _max : v))
#endif

/**
 * Builds an unsigned integer value constructed with color components.
 * @param a Opacity of the color. 0x00 is totally transparent. 0xFF is totally
 * opaque.
 * @param r Intensity for the @b Red component.
 * @param g Intensity for the @b Green component.
 * @param b Intensity for the @b Blue component.
 * @return The color value as an unsigned 32 bits integer.
 **/
#define ARGB(a, r, g, b)    (((a) << 24) | ((r) << 16) | ((g) << 8) | (b))

/**
 * Builds a color value.
 * @param r Intensity for the @b Red component.
 * @param g Intensity for the @b Green component.
 * @param b Intensity for the @b Blue component.
 * @return The color value as an unsigned 32 bits integer.
 **/
#define RGB(r, g, b)        ARGB(0xFF, r, g, b)

/**
 * Extracts the Alpha component of a color value.
 * @param argb Color value as an 32 bits integer.
 * @return The alpha component. 0x00 is totally transparent. 0xFF is totally
 * opaque.
 **/
#define ALPHA_H(argb)       (((argb) >> 24) & 0x000000FF)

/**
 * Extracts the Red component of a color value.
 * @param argb Color value as an 32 bits integer.
 * @return The intensity of the Red component.
 **/
#define RED_H(argb)         (((argb) >> 16) & 0x000000FF)

/**
 * Extracts the Green component of a color value.
 * @param argb Color value as an 32 bits integer.
 * @return The intensity of the Green component.
 **/
#define GREEN_H(argb)       (((argb) >>  8) & 0x000000FF)

/**
 * Extracts the Blue component of a color value.
 * @param argb Color value as an 32 bits integer.
 * @return The intensity of the Blue component.
 **/
#define BLUE_H(argb)        ((argb) & 0x000000FF)

/**
 * Extracts the Alpha component of a color value.
 * @param argb Color value as an 32 bits integer.
 * @return The alpha component as a float number. 0.0 is totally transparent.
 * 1.0 is totally opaque.
 **/
#define ALPHA_F(argb)       (((float)ALPHA_H(argb)) / 255.0f)

/**
 * Extracts the Red component of a color value.
 * @param argb Color value as an 32 bits integer.
 * @return The intensity of the Red component as a float number.
 **/
#define RED_F(argb)         (((float)RED_H(argb)) / 255.0f)

/**
 * Extracts the Green component of a color value.
 * @param argb Color value as an 32 bits integer.
 * @return The intensity of the Green component as a float number.
 **/
#define GREEN_F(argb)       (((float)GREEN_H(argb)) / 255.0f)

/**
 * Extracts the Blue component of a color value.
 * @param argb Color value as an 32 bits integer.
 * @return The intensity of the Blue component as a float number.
 **/
#define BLUE_F(argb)        (((float)BLUE_H(argb)) / 255.0f)
///@} sf_general
#endif /* __SFSTD_H_DEFINED__ */
// vim:ft=c
