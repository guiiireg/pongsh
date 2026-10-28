#include "my.h"
#include "my_printf_internal.h"

/**
** @brief Writes a literal character of the format string.
**
** @param format The format string being processed.
** @param index The current position, advanced by one character.
**
** @return The number of bytes written, or -1 on failure.
*/
int pf_plain(char const *format, int *index)
{
    int status = my_putchar(format[*index]);

    if (status == -1) {
        return (-1);
    }
    *index += 1;
    return (status);
}

/**
** @brief Writes a percent sign, literal or a conversion.
**
** The %% pair writes a single percent sign. A known conversion is
** delegated to pf_convert. Anything else is written literally.
**
** @param args The variadic arguments of my_printf.
** @param format The format string being processed.
** @param index The current position, advanced by the consumed
**              characters.
**
** @return The number of bytes written, or -1 on failure.
*/
int pf_percent(va_list *args, char const *format, int *index)
{
    char spec = format[*index + 1];
    int status;

    if (spec == '%') {
        status = my_putchar('%');
        if (status == -1) {
            return (-1);
        }
        *index += 2;
        return (status);
    }
    status = pf_convert(args, spec);

    if (status == PF_NOT_CONVERSION) {
        status = my_putchar('%');
        if (status == -1) {
            return (-1);
        }
        *index += 1;
        return (status);
    }
    if (status == -1) {
        return (-1);
    }
    *index += 2;
    return (status);
}

/**
** @brief Dispatches one directive of the format string.
**
** @param args The variadic arguments of my_printf.
** @param format The format string being processed.
** @param index The current position, advanced by the directive.
**
** @return The number of bytes written, or -1 on failure.
*/
int pf_directive(va_list *args, char const *format, int *index)
{
    if (format[*index] == '%') {
        return (pf_percent(args, format, index));
    }
    return (pf_plain(format, index));
}
