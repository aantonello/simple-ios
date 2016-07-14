/**
 * \file
 * Defines the debugging functions.
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
#import "sfdebug.h"

/**
 * Print debugging information in the standard \c stderr file.
 * \param fmt Zero terminated string with format specification.
 * \param list List of values to be formated according to \a fmt.
 *//* --------------------------------------------------------------------- */
void __sf_printv(const char* fmt, va_list list)
{
    vfprintf(stderr, fmt, list);
}

/**
 * Print debugging output in the standard \c stderr file.
 * \param fmt Zero terminated string with format specification.
 * \param ... List of values to be formated according to \a fmt.
 *//* --------------------------------------------------------------------- */
void __sf_print(const char* fmt, ...)
{
    va_list list;

    va_start(list, fmt);
    __sf_printv(fmt, list);
    va_end(list);
}

/**
 * Print debugging output in the standard \c stderr file.
 * \param file Name of the file.
 * \param line Number of current line.
 * \param fmt Zero terminated string with format specification.
 * \param ... List of values to be formated according to \a fmt.
 *//* --------------------------------------------------------------------- */
void __sf_trace(const char* file, int line, const char* fmt, ...)
{
    va_list list;
    char szBuff[1024];
    char *fname;

    /* We need to separate the path from the file name. We don't need to print
     * the path, just the file name.
     */
    fname = strrchr(file, '/');
    fname++;

    snprintf(szBuff, 1024, "%s @ %d: %s", fname, line, fmt);

    va_start(list, fmt);
    __sf_printv(szBuff, list);
    va_end(list);
}

/**
 * Flushes a binary array into standard \c stderr file.
 * \param head Text to be written before the binary array dump. Can be NULL.
 * \param data Pointer to the memory where the data is.
 * \param size Length of the data pointed by \a data, in bytes.
 * \param tail Text to be written after the binary array dump. Can be NULL.
 *//* --------------------------------------------------------------------- */
void __sf_flush(const char* head, const void* data, size_t size, const char* tail)
{
    const uint8_t* dump = (const uint8_t*)data;
    const uint8_t* end  = dump + size;

    if (head) __sf_print("%s", head);

    while (dump < end) __sf_print(" %02X", *dump++);

    if (tail) __sf_print("%s", tail);
}

/**
 * Assert some condition and prints the message in the \c stderr file.
 * \param file Name of the file.
 * \param line Number of current line.
 * \param fmt Zero terminated string with format specification.
 * \param ... List of values to be formated according to \a fmt.
 *//* --------------------------------------------------------------------- */
void __sf_assert(const char* file, int line, const char* fmt, ...)
{
    va_list list;
    char szBuff[1024];
    char *fname;

    /* We need to separate the path from the file name. We don't need to print
     * the path, just the file name.
     */
    fname = strrchr(file, '/');
    fname++;

    snprintf(szBuff, 1024, "Assetion Failed in '%s' @ %d: '%s'", file, line, fmt);

    va_start(list, fmt);
    __sf_printv(szBuff, list);
    va_end(list);
}

/**
 * Print debugging output in the standard \c stderr file.
 * \param file Name of the file.
 * \param line Number of current line.
 * \param func Name of the current function.
 * \param fmt Zero terminated string with format specification.
 * \param ... List of values to be formated according to \a fmt.
 *//* --------------------------------------------------------------------- */
void __sf_tracef(const char* file, int line, const char* func, const char* fmt, ...)
{
    va_list list;
    char szBuff[1024];
    char *fname;

    /* We need to separate the path from the file name. We don't need to print
     * the path, just the file name.
     */
    fname = strrchr(file, '/');
    fname++;

    snprintf(szBuff, 1024, "%s @ %d: %s %s", fname, line, func, fmt);

    va_start(list, fmt);
    __sf_printv(szBuff, list);
    va_end(list);
}
// vim:syntax=objc.doxygen
