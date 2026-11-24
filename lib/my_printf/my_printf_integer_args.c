#include "../../include/my_printf_internal.h"

static intmax_t read_signed(va_list *args, printf_length_t length)
{
    if (length == PRINTF_J)
        return PRINTF_READ_INTMAX(args);
    if (length == PRINTF_LL)
        return va_arg(*args, long long);
    if (length == PRINTF_L)
        return va_arg(*args, long);
    if (length == PRINTF_H)
        return (short)va_arg(*args, int);
    if (length == PRINTF_HH)
        return (signed char)va_arg(*args, int);
    return va_arg(*args, int);
}

static uintmax_t read_unsigned(va_list *args, printf_length_t length)
{
    if (length == PRINTF_J)
        return PRINTF_READ_UINTMAX(args);
    if (length == PRINTF_LL)
        return va_arg(*args, unsigned long long);
    if (length == PRINTF_L)
        return va_arg(*args, unsigned long);
    if (length == PRINTF_H)
        return (unsigned short)va_arg(*args, unsigned int);
    if (length == PRINTF_HH)
        return (unsigned char)va_arg(*args, unsigned int);
    return va_arg(*args, unsigned int);
}

static void set_signed_value(printf_field_t *field, intmax_t number,
    uintmax_t *value)
{
    *value = (uintmax_t)number;
    if (number < 0) {
        field->prefix = "-";
        *value = 0 - *value;
    }
}

int my_printf_read_integer(printf_field_t *field, printf_spec_t const *spec,
    va_list *args, uintmax_t *value)
{
    if (spec->type == 'p' && spec->length == PRINTF_DEFAULT) {
        *value = (uintptr_t)va_arg(*args, void *);
        return 0;
    }
    if (spec->type == 'd' || spec->type == 'i') {
        set_signed_value(field, read_signed(args, spec->length), value);
        return 0;
    }
    if (spec->type == 'u' || spec->type == 'o' || spec->type == 'x'
        || spec->type == 'X') {
        *value = read_unsigned(args, spec->length);
        return 0;
    }
    return -1;
}
