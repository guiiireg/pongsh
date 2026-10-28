#include <stdarg.h>

#include "my_printf_internal.h"

/**
** @brief Writes a formatted string to the standard output.
**
** Plain characters, %% and the %c %s %d %i %u %o %x %X %p
** conversions are handled. Flags, width and precision are not
** implemented yet. An unsupported specifier is written literally.
**
** @param format The format string.
** @param ... The values to convert, one per conversion.
**
** @return The number of bytes written, or -1 on failure.
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
