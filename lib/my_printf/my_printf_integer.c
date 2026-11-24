#include "../../include/my_printf_internal.h"
#include <limits.h>

static unsigned int number_base(char type)
{
    if (type == 'o')
        return 8;
    if (type == 'x' || type == 'X' || type == 'p')
        return 16;
    return 10;
}

static void set_prefix(printf_field_t *field, printf_spec_t const *spec,
    uintmax_t value)
{
    if (!field->prefix && (spec->type == 'd' || spec->type == 'i')) {
        if (spec->flags & PRINTF_PLUS)
            field->prefix = "+";
        if (!field->prefix && (spec->flags & PRINTF_SPACE))
            field->prefix = " ";
    }
    if (field->prefix)
        field->prefix_length = 1;
    if (spec->type == 'p' || ((spec->flags & PRINTF_ALT) && value != 0
        && (spec->type == 'x' || spec->type == 'X'))) {
        field->prefix = "0x";
        if (spec->type == 'X')
            field->prefix = "0X";
        field->prefix_length = 2;
    }
}

static void build_digits(printf_field_t *field, printf_spec_t const *spec,
    uintmax_t value, char *end)
{
    unsigned int base = number_base(spec->type);
    char const *digits = "0123456789abcdef";

    if (spec->type == 'X')
        digits = "0123456789ABCDEF";
    field->text = end;
    if (!value && spec->precision == 0 && spec->type != 'p')
        return;
    do {
        end--;
        *end = digits[value % base];
        field->length++;
        value /= base;
    } while (value);
    field->text = end;
}

static void set_zeros(printf_field_t *field, printf_spec_t const *spec)
{
    int digits_width = spec->width - field->prefix_length;

    if (spec->precision > field->length)
        field->zeros = spec->precision - field->length;
    if ((spec->flags & PRINTF_ALT) && spec->type == 'o' && !field->zeros) {
        if (!field->length || field->text[0] != '0')
            field->zeros = 1;
    }
    if ((spec->flags & PRINTF_ZERO) && !(spec->flags & PRINTF_LEFT)
        && spec->precision < 0 && digits_width > field->length
        && digits_width - field->length > field->zeros)
        field->zeros = digits_width - field->length;
}

int my_printf_integer(int *out, printf_spec_t const *spec,
    va_list *args)
{
    printf_field_t field = {0};
    char digits[sizeof(uintmax_t) * CHAR_BIT];
    uintmax_t value;

    if (my_printf_read_integer(&field, spec, args, &value) < 0)
        return -1;
    build_digits(&field, spec, value, digits + sizeof(digits));
    set_prefix(&field, spec, value);
    set_zeros(&field, spec);
    return my_printf_field(out, spec, &field);
}
