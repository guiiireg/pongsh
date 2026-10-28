#include "my.h"
#include "my_printf_internal.h"

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
int emit_number_left(pf_number_t const *number)
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
int emit_number_zero(pf_number_t const *number)
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
int emit_number_right(pf_number_t const *number)
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
