#include "my_printf_internal.h"
#include <limits.h>

static int read_number(char const **format, va_list *args, int *number)
{
    int digit;

    if (**format == '*') {
        (*format)++;
        *number = va_arg(*args, int);
        return 0;
    }
    *number = 0;
    while (**format >= '0' && **format <= '9') {
        digit = **format - '0';
        if (*number > (INT_MAX - digit) / 10)
            return -1;
        *number = *number * 10 + digit;
        (*format)++;
    }
    return 0;
}

static int read_width(char const **format, printf_spec_t *spec, va_list *args)
{
    if (read_number(format, args, &spec->width) < 0)
        return -1;
    if (spec->width == INT_MIN)
        return -1;
    if (spec->width < 0) {
        spec->flags |= PRINTF_LEFT;
        spec->width = -spec->width;
    }
    return 0;
}

static int read_precision(char const **format, printf_spec_t *spec,
    va_list *args)
{
    if (**format != '.')
        return 0;
    (*format)++;
    return read_number(format, args, &spec->precision);
}

int my_printf_read_dimensions(char const **format, printf_spec_t *spec,
    va_list *args)
{
    if (read_width(format, spec, args) < 0)
        return -1;
    return read_precision(format, spec, args);
}
