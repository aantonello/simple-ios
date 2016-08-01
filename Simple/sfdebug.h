/**
 * \file
 * Declares macros and debugging functions.
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
#import <Foundation/Foundation.h>
#include <assert.h>

/**
 * \defgroup sf_debug Debug
 * Macros and functions for debugging.
 * @{ *//* ---------------------------------------------------------------- */

/**
 * Shortcut to convert an NSString object to UTF-8 char array.
 * @param x The NSString object to convert.
 **/
#define    sfutf8(x)            ([(x) cStringUsingEncoding:NSUTF8StringEncoding])

/**
 * Shortcut to convert a NSString into UTF-8 char array.
 * @param x The NSString object to convert.
 * @remarks This macro should been used instead of \c sfutf8() becouse it
 * checks for parameter nulity before making object calls.
 **/
#define     sfstr(x)            ((x) ? sfutf8(x) : "nil")

/**
 * Alias for \c sfstr function macro.
 * @since 1.3
 **/
#define     sfT                 sfstr

/**
 * Macro to print the class name of an object.
 * @param o Object to get its class name. If \b nil, "nil" will be returned.
 **/
#define     sfclass(o)          ((o) ? object_getClassName(o) : "nil")

/**
 * Shortcut to get object descriptions in debugging output.
 * @param x Object to get its description.
 **/
#define     sfdesc(x)           sfclass(x)

/**
 * Boolean to string converter.
 * @param x Boolean value or expression.
 * @returns "TRUE" when @a x results in a value different from 0. Otherwise
 * "FALSE".
 **/
#define     sfboolT(x)                  ((x) ? "TRUE" : "FALSE")

#ifdef DEBUG

# define    sfdebug(fmt, ...)           __sf_print(fmt, ##__VA_ARGS__)
# define    sftrace(fmt, ...)           __sf_trace(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
# define    sfflush(h, b, s, t)         __sf_flush(h, b, s, t)
# define    sfassert(b, fmt, ...)       do { if (!(b)) { __sf_assert(__FILE__, __LINE__, fmt, ##__VA_ARGS__); abort(); } } while (0)
# define    sftracef(fmt, ...)          __sf_tracef(__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)
/* Documentation {{{ */
/**
 * @def sfdebug(fmt, ...)
 * Writes text to the standard output.
 * Different of @c NSLog() function this works only with C strings. If you
 * need to write NSString with this macro use the @c sfutf8() macro converter.
 * @param fmt Formatter string. The same format especification of standard @c
 * printf() function is supported.
 * @param ... Values to format. This parameter is optional.
 * @returns Nothing.
 **/

/**
 * @def sftrace(fmt, ...)
 * Writes text to the standard ouput.
 * This macros is the same as @c sfdebug() with the addition of prepending the
 * file name and line number of the source. The macros @c __FILE__ and @c
 * __LINE__ are used in the output.
 * @param fmt Formatter string. The same format especification of standard @c
 * printf() function is supported.
 * @param ... Values to format. This parameter is optional.
 * @returns Nothing.
 **/

/**
 * @def sfflush(h, b, s, t)
 * Writes a byte array in the standard output.
 * This macro will format every byte value into its hexadecimal
 * representation. Each byte will be prepended with a space character. That
 * is, for an array with values `{ 0x00, 0x09, 0x0A, 0xA0 }` this function
 * will write ` 00 09 0A A0`.
 * @param h A header string to be written before the array data.
 * @param b Address of the data to write.
 * @param s Length of the memory pointed by @a b.
 * @param t A tail string to be written after the array data.
 * @returns Nothing
 * @note @a h and @a t string will be written as is. No separator character
 * nor carriege return or line feed will be added.
 **/

/**
 * @def sfassert(b, fmt, ...)
 * Provokes an assertion failure in the line if the expression results in a @b
 * FALSE value.
 * @param b Expression thats evaluate to @b TRUE or @b FALSE.
 * @param fmt A string with a message to be written in the standard ouput.
 * Optionaly this string may contain format especifiers to output some values.
 * @param ... Optional. A list of values to format into the @a fmt string.
 * @returns Nothing.
 * @remarks If the expression passed at @a b evaluates to an @b FALSE value
 * the code will stop with an `int 3` assembly interruption.
 **/

/**
 * @def sftracef(fmt, ...)
 * Writes text to the standard ouput.
 * This macros is the same as @c sftrace() with the addition of including the
 * function name in the output. The prefix output will have the following
 * format:
 * <pre>
 * "__FILE__ __func__ (line __LINE__): "
 * </pre>
 * Folowed by the string and optional formated values passed to the macro.
 * @param fmt Formatter string. The same format especification of standard @c
 * printf() function is supported.
 * @param ... Values to format. This parameter is optional.
 * @returns Nothing.
 **/
/* }}} Documentation */
#else

# define    sfdebug(...)
# define    sftrace(...)
# define    sfflush(h,b,s,t)
# define    sfassert(...)
# define    sftracef(...)

#endif /* NDEBUG */

#ifdef __cplusplus
extern "C" {
#endif

/** @cond SF_PRIVATE */
void __sf_print(const char* fmt, ...);
void __sf_trace(const char* file, int line, const char* fmt, ...);
void __sf_flush(const char* head, const void* data, size_t size, const char* tail);
void __sf_assert(const char* file, int line, const char* fmt, ...);
void __sf_tracef(const char* file, int line, const char* func, const char* fmt, ...);
/** @endcond */

#ifdef __cplusplus
}
#endif
///@} sf_debug
// vim:ft=objc syntax=objc.doxygen
