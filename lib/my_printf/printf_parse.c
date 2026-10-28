#include "my.h"
#include "my_printf_internal.h"

/**
 * @brief Checks whether a character is a flag.
 *
 * @param c The character to check.
 *
 * @return 1 if the character is a flag, 0 otherwise.
 */
static int pf_is_flag(char c)
{
    switch (c) {
        case '-':
        case '+':
        case ' ':
        case '0':
        case '#':
            return (1);
        default:
            return (0);
    }
}

/**
 * @brief Records one flag in the specification.
 *
 * @param flag The flag character.
 * @param spec The specification being parsed.
 */
static void pf_set_flag(char flag, pf_spec_t *spec)
{
    switch (flag) {
        case '-':
            spec->left = 1;
            break;
        case '+':
            spec->plus = 1;
            break;
        case ' ':
            spec->space = 1;
            break;
        case '0':
            spec->zero = 1;
            break;
        case '#':
            spec->hash = 1;
            break;
        default:
            break;
    }
}

/**
 * @brief Parses the flags of a conversion specification.
 *
 * @param format The format string being parsed.
 * @param index The current position, advanced past the flags.
 * @param spec The specification being parsed.
 */
static void pf_parse_flags(char const *format, int *index, pf_spec_t *spec)
{
    while (pf_is_flag(format[*index]) == 1) {
        pf_set_flag(format[*index], spec);
        *index += 1;
    }
}

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
static int pf_parse_width(va_list *args, char const *format, int *index,
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
static int pf_parse_precision(va_list *args, char const *format, int *index,
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

/**
 * @brief Checks whether a character is a supported conversion.
 *
 * @param spec The conversion specifier.
 *
 * @return 1 for a supported conversion, 0 otherwise.
 */
static int pf_is_conversion(char spec)
{
    switch (spec) {
        case 'c':
        case 's':
        case 'd':
        case 'i':
        case 'u':
        case 'o':
        case 'x':
        case 'X':
        case 'p':
            return (1);
        default:
            return (0);
    }
}

/**
 * @brief Parses a full conversion specification.
 *
 * Grammar: %[flags][width][.precision]conversion.
 *
 * @param args The variadic arguments of my_printf.
 * @param format The format string being parsed.
 * @param index The current position, advanced past the specification.
 * @param spec The parsed specification.
 *
 * @return 0 on success, or PF_NOT_CONVERSION for an unsupported
 *         specifier.
 */
int pf_parse(va_list *args, char const *format, int *index, pf_spec_t *spec)
{
    my_bzero(spec, sizeof(*spec));
    pf_parse_flags(format, index, spec);
    pf_parse_width(args, format, index, spec);
    pf_parse_precision(args, format, index, spec);
    if (pf_is_conversion(format[*index]) != 1) {
        return (PF_NOT_CONVERSION);
    }
    spec->spec = format[*index];
    *index += 1;
    return (0);
}
