#include <stddef.h>

#include "my_printf_internal.h"

/**
** @brief Walks the format string and writes each directive.
**
** @param args The variadic arguments of my_printf.
** @param format The format string to process.
**
** @return The number of bytes written, or -1 on failure.
*/
int pf_format(va_list *args, char const *format)
{
    int index = 0;
    int emitted;
    int total = 0;

    if (format == NULL) {
        return (-1);
    }
    while (format[index] != '\0') {
        emitted = pf_directive(args, format, &index);
        if (emitted == -1) {
            return (-1);
        }
        total += emitted;
    }
    return (total);
}
