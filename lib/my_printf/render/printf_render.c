#include "my.h"
#include "my_printf_internal.h"

/**
 * @brief Computes the field padding of a number.
 *
 * The width counts the prefix and the precision zeros.
 *
 * @param spec The parsed specification.
 * @param number The computed layout of the number.
 *
 * @return The number of padding characters.
 */
static int pf_number_pad(pf_spec_t const *spec, pf_number_t const *number)
{
    int body = my_strlen(number->prefix) + number->zeros + number->digits;

    if (spec->width > body) {
        return (spec->width - body);
    }
    return (0);
}

/**
 * @brief Writes a number applying flags, width and precision.
 *
 * The flag interactions follow the manual: the - flag ignores 0, a
 * precision on an integer conversion ignores 0, and the width counts
 * the sign and the alternate form prefix.
 *
 * @param spec The parsed specification.
 * @param magnitude The unsigned magnitude to write.
 * @param base The digits of the base.
 *
 * @return The number of bytes written, or -1 on failure.
 */
int pf_write_number(pf_spec_t const *spec, unsigned long magnitude,
    char const *base)
{
    pf_number_t number;

    number.base = base;
    number.magnitude = magnitude;
    number.digits = pf_count_digits(magnitude, my_strlen(base));
    if (spec->has_precision && spec->precision == 0 && magnitude == 0) {
        number.digits = 0;
    }
    number.zeros = pf_leading_zeros(spec, magnitude, base);
    number.prefix = pf_number_prefix(spec, magnitude, number.zeros,
        number.digits);
    number.pad = pf_number_pad(spec, &number);
    if (spec->left) {
        return (emit_number_left(&number));
    }
    if (spec->zero && !spec->has_precision) {
        return (emit_number_zero(&number));
    }
    return (emit_number_right(&number));
}
