#include "my.h"
#include "my_printf_internal.h"

/**
 * @brief Maps a conversion specifier to its base digits.
 *
 * @param spec The conversion specifier.
 *
 * @return The digits of the base, in order.
 */
static char const *pf_number_base(char spec)
{
    switch (spec) {
        case 'o':
            return ("01234567");
        case 'x':
        case 'p':
            return ("0123456789abcdef");
        case 'X':
            return ("0123456789ABCDEF");
        default:
            return ("0123456789");
    }
}

/**
 * @brief Renders a %d, %i, %u, %o, %x, %X or %p conversion.
 *
 * INT_MIN cannot be negated as an int. Negating it as an unsigned
 * value instead is always well defined and yields its magnitude.
 *
 * @param args The variadic arguments of my_printf.
 * @param spec The parsed specification.
 *
 * @return The number of bytes written, or -1 on failure.
 */
int pf_render_number(va_list *args, pf_spec_t *spec)
{
    unsigned long magnitude = 0;
    int value = 0;

    if (spec->spec == 'd' || spec->spec == 'i') {
        value = va_arg(*args, int);
        if (value < 0) {
            spec->negative = 1;
            magnitude = -(unsigned int)value;
        } else {
            magnitude = (unsigned long)value;
        }
    } else if (spec->spec == 'p') {
        magnitude = (unsigned long)va_arg(*args, void *);
    } else {
        magnitude = va_arg(*args, unsigned int);
    }
    return (pf_write_number(spec, magnitude, pf_number_base(spec->spec)));
}
