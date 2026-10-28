#include <unistd.h>

#include "my.h"
#include "my_printf_internal.h"

/**
 * @brief Writes the digits of an unsigned value in the given base.
 *
 * The digits are built in reverse in a local buffer, then written with
 * a single write call.
 *
 * @param value The value to write.
 * @param base The digits of the base, in order.
 *
 * @return The number of bytes written, or -1 on failure.
 */
int pf_base(unsigned long value, char const *base)
{
    char digits[65];
    unsigned long divisor = (unsigned long)my_strlen(base);
    int i = 65;
    int status;

    while (i > 0) {
        i -= 1;
        digits[i] = base[value % divisor];
        value /= divisor;
        if (value == 0) {
            break;
        }
    }
    status = write(STDOUT_FILENO, &digits[i], 65 - i);
    if (status != 65 - i) {
        return (-1);
    }
    return (status);
}

/**
 * @brief Counts the digits of an unsigned value in the given base.
 *
 * @param value The value to count digits of.
 * @param base_len The length of the base.
 *
 * @return The number of digits, at least 1.
 */
int pf_count_digits(unsigned long value, int base_len)
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
int pf_leading_zeros(pf_spec_t const *spec, unsigned long magnitude,
    char const *base)
{
    int digits = pf_count_digits(magnitude, my_strlen(base));

    if (spec->has_precision && spec->precision > digits) {
        return (spec->precision - digits);
    }
    return (0);
}
