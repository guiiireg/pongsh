#include "my.h"
#include "my_printf_internal.h"

/**
 * @brief Writes a literal character of the format string.
 *
 * @param format The format string being processed.
 * @param index The current position, advanced by one character.
 *
 * @return The number of bytes written, or -1 on failure.
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
 * @brief Writes a percent sign, a %% pair or a conversion.
 *
 * An unsupported specifier is written literally: the consumed flags
 * and width are emitted, then the parsing resumes after the %.
 *
 * @param args The variadic arguments of my_printf.
 * @param format The format string being processed.
 * @param index The current position, advanced by the directive.
 *
 * @return The number of bytes written, or -1 on failure.
 */
int pf_percent(va_list *args, char const *format, int *index)
{
    pf_spec_t spec;
    int start = *index;
    int status;

    if (format[start + 1] == '%') {
        status = my_putchar('%');
        if (status == -1) {
            return (-1);
        }
        *index = start + 2;
        return (status);
    }
    *index = start + 1;
    if (pf_parse(args, format, index, &spec) == 0) {
        return (pf_run(args, &spec));
    }
    if (*index == start + 1) {
        return (my_putchar('%'));
    }
    return (pf_write_chars(&format[start], *index - start));
}

/**
 * @brief Dispatches one directive of the format string.
 *
 * @param args The variadic arguments of my_printf.
 * @param format The format string being processed.
 * @param index The current position, advanced by the directive.
 *
 * @return The number of bytes written, or -1 on failure.
 */
int pf_directive(va_list *args, char const *format, int *index)
{
    if (format[*index] == '%') {
        return (pf_percent(args, format, index));
    }
    return (pf_plain(format, index));
}
