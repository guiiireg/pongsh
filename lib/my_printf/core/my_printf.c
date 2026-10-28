#include <stdarg.h>

#include "my_printf_internal.h"

/**
 * @brief Writes a formatted string to the standard output.
 *
 * Supports the %% and %c %s %d %i %u %o %x %X %p conversions, the
 * - 0 + space # flags, a numeric or * field width and a numeric or
 * * precision. An unsupported specifier is written literally.
 *
 * @param format The format string.
 * @param ... The values to convert, one per conversion.
 *
 * @return The number of bytes written, or -1 on failure.
 */
int my_printf(char const *format, ...)
{
    va_list args;
    int result;

    va_start(args, format);
    result = pf_format(&args, format);
    va_end(args);
    return (result);
}
