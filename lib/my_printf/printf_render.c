#include "my.h"
#include "my_printf_internal.h"

/* The computed layout of a number rendering. */
typedef struct pf_number_s {
    char const *prefix;
    char const *base;
    unsigned long magnitude;
    int zeros;
    int pad;
    int digits;
} pf_number_t;

/**
 * @brief Writes the digits of an unsigned value in the given base.
 *
 * @param value The value to write.
 * @param base The digits of the base, in order.
 *
 * @return The number of bytes written, or -1 on failure.
 */
static int pf_base(unsigned long value, char const *base)
{
    unsigned long divisor = (unsigned long)my_strlen(base);
    int emitted = 0;
    int status;

    if (value >= divisor) {
        status = pf_base(value / divisor, base);
        if (status == -1) {
            return (-1);
        }
        emitted += status;
    }
    status = my_putchar(base[value % divisor]);
    if (status == -1) {
        return (-1);
    }
    return (emitted + status);
}

/**
 * @brief Counts the digits of an unsigned value in the given base.
 *
 * @param value The value to count digits of.
 * @param base_len The length of the base.
 *
 * @return The number of digits, at least 1.
 */
static int pf_count_digits(unsigned long value, int base_len)
{
    int count = 1;

    while (value >= (unsigned long)base_len) {
        value /= (unsigned long)base_len;
        count += 1;
    }
    return (count);
}

/**
 * @brief Computes the precision zero padding of a number.
 *
 * @param spec The parsed specification.
 * @param magnitude The unsigned magnitude to write.
 * @param base The digits of the base.
 *
 * @return The number of leading zeros required by the precision.
 */
static int pf_leading_zeros(pf_spec_t const *spec, unsigned long magnitude,
    char const *base)
{
    int digits = pf_count_digits(magnitude, my_strlen(base));

    if (spec->has_precision && spec->precision > digits) {
        return (spec->precision - digits);
    }
    return (0);
}

/**
 * @brief Computes the alternate form prefix of an unsigned value.
 *
 * @param spec The parsed specification.
 * @param magnitude The unsigned magnitude to write.
 * @param zeros The precision zero padding.
 * @param digits The number of digits that will be written.
 *
 * @return The prefix, possibly empty.
 */
static char const *pf_hash_prefix(pf_spec_t const *spec,
    unsigned long magnitude, int zeros, int digits)
{
    if (spec->spec == 'p') {
        return ("0x");
    }
    if (spec->hash == 0) {
        return ("");
    }
    switch (spec->spec) {
        case 'x':
            if (magnitude != 0) {
                return ("0x");
            }
            break;
        case 'X':
            if (magnitude != 0) {
                return ("0X");
            }
            break;
        case 'o':
            if (zeros == 0 && (magnitude != 0 || digits == 0)) {
                return ("0");
            }
            break;
        default:
            break;
    }
    return ("");
}

/**
 * @brief Computes the prefix of a number.
 *
 * The - and + signs take precedence over the space flag.
 *
 * @param spec The parsed specification.
 * @param magnitude The unsigned magnitude to write.
 * @param zeros The precision zero padding.
 * @param digits The number of digits that will be written.
 *
 * @return The prefix, possibly empty.
 */
static char const *pf_number_prefix(pf_spec_t const *spec,
    unsigned long magnitude, int zeros, int digits)
{
    if (spec->negative) {
        return ("-");
    }
    switch (spec->spec) {
        case 'd':
        case 'i':
            if (spec->plus) {
                return ("+");
            }
            if (spec->space) {
                return (" ");
            }
            return ("");
        default:
            return (pf_hash_prefix(spec, magnitude, zeros, digits));
    }
}

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
 * @brief Writes the digits of the number layout, if any.
 *
 * @param number The computed layout of the number.
 *
 * @return The number of bytes written, or -1 on failure.
 */
static int emit_number_digits(pf_number_t const *number)
{
    if (number->digits > 0) {
        return (pf_base(number->magnitude, number->base));
    }
    return (0);
}

/**
 * @brief Writes a number, left aligned in its field.
 *
 * @param number The computed layout of the number.
 *
 * @return The number of bytes written, or -1 on failure.
 */
static int emit_number_left(pf_number_t const *number)
{
    int total = 0;

    total = pf_add_status(my_putstr(number->prefix), total);
    if (total != -1) {
        total = pf_add_status(pf_repeat('0', number->zeros), total);
    }
    if (total != -1) {
        total = pf_add_status(emit_number_digits(number), total);
    }
    if (total != -1) {
        total = pf_add_status(pf_repeat(' ', number->pad), total);
    }
    return (total);
}

/**
 * @brief Writes a number, zero padded up to the field width.
 *
 * The zeros are written after the prefix, between it and the digits.
 *
 * @param number The computed layout of the number.
 *
 * @return The number of bytes written, or -1 on failure.
 */
static int emit_number_zero(pf_number_t const *number)
{
    int total = 0;

    total = pf_add_status(my_putstr(number->prefix), total);
    if (total != -1) {
        total = pf_add_status(pf_repeat('0', number->zeros + number->pad),
            total);
    }
    if (total != -1) {
        total = pf_add_status(emit_number_digits(number), total);
    }
    return (total);
}

/**
 * @brief Writes a number, right aligned in its field.
 *
 * @param number The computed layout of the number.
 *
 * @return The number of bytes written, or -1 on failure.
 */
static int emit_number_right(pf_number_t const *number)
{
    int total = 0;

    total = pf_add_status(pf_repeat(' ', number->pad), total);
    if (total != -1) {
        total = pf_add_status(my_putstr(number->prefix), total);
    }
    if (total != -1) {
        total = pf_add_status(pf_repeat('0', number->zeros), total);
    }
    if (total != -1) {
        total = pf_add_status(emit_number_digits(number), total);
    }
    return (total);
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
