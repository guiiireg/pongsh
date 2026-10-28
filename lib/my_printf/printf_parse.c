#include "my.h"
#include "my_printf_internal.h"

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
 * Grammar: %[flags][width][.precision]conversion. The index must point
 * right after the introducing %.
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
