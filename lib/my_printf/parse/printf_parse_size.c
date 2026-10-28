#include "my.h"
#include "my_printf_internal.h"

/**
 * @brief Parses a decimal number written in the format string.
 *
 * @param format The format string being parsed.
 * @param index The current position, advanced past the digits.
 *
 * @return The parsed number.
 */
static int pf_parse_digits(char const *format, int *index)
{
    int value = 0;

    while (my_isdigit(format[*index]) == 1) {
        value = value * 10 + (format[*index] - '0');
        *index += 1;
    }
    return (value);
}

/**
 * @brief Parses the field width of a conversion specification.
 *
 * The * form reads the width from the arguments; a negative width
 * acts as the - flag followed by a positive width.
 *
 * @param args The variadic arguments of my_printf.
 * @param format The format string being parsed.
 * @param index The current position, advanced past the width.
 * @param spec The specification being parsed.
 *
 * @return 0 on success, or -1 on failure.
 */
int pf_parse_width(va_list *args, char const *format, int *index,
    pf_spec_t *spec)
{
    int value;

    if (format[*index] != '*') {
        spec->width = pf_parse_digits(format, index);
        return (0);
    }
    value = va_arg(*args, int);
    *index += 1;
    if (value < 0) {
        spec->left = 1;
        value = -value;
    }
    spec->width = value;
    return (0);
}

/**
 * @brief Parses the precision of a conversion specification.
 *
 * The * form reads the precision from the arguments; a negative
 * precision is taken as if it were omitted.
 *
 * @param args The variadic arguments of my_printf.
 * @param format The format string being parsed.
 * @param index The current position, advanced past the precision.
 * @param spec The specification being parsed.
 *
 * @return 0 on success, or -1 on failure.
 */
int pf_parse_precision(va_list *args, char const *format, int *index,
    pf_spec_t *spec)
{
    int value;

    if (format[*index] != '.') {
        return (0);
    }
    *index += 1;
    if (format[*index] != '*') {
        spec->has_precision = 1;
        spec->precision = pf_parse_digits(format, index);
        return (0);
    }
    value = va_arg(*args, int);
    *index += 1;
    if (value >= 0) {
        spec->has_precision = 1;
        spec->precision = value;
    }
    return (0);
}
