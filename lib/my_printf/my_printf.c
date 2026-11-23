#include "my.h"
#include "my_printf_internal.h"
#include <limits.h>

static int print_text(printf_output_t *out, printf_spec_t const *spec,
    char const *text)
{
    printf_field_t field = {.text = text};

    if (!text)
        field.text = "(null)";
    while (spec->precision < 0 || field.length < spec->precision) {
        if (field.length == INT_MAX)
            return -1;
        if (!field.text[field.length])
            break;
        field.length++;
    }
    return my_printf_field(out, spec, &field);
}

static int print_argument(printf_output_t *out, printf_spec_t const *spec,
    va_list *args)
{
    char byte;
    printf_field_t field = {.text = &byte, .length = 1};

    if (spec->type == 's' && spec->length == PRINTF_DEFAULT)
        return print_text(out, spec, va_arg(*args, char *));
    if (spec->type == 'c' && spec->length == PRINTF_DEFAULT) {
        byte = (char)(unsigned char)va_arg(*args, int);
        return my_printf_field(out, spec, &field);
    }
    if (spec->type == '%' && spec->length == PRINTF_DEFAULT)
        return my_printf_write(out, "%", 1);
    return my_printf_integer(out, spec, args);
}

static int print_format(char const *format, va_list *args)
{
    printf_output_t out = {0};
    printf_spec_t spec;
    char const *start;

    while (*format) {
        start = format;
        while (*format && *format != '%')
            format++;
        if (my_printf_write(&out, start, (size_t)(format - start)) < 0)
            return -1;
        if (!*format)
            break;
        format++;
        if (my_printf_parse(&format, &spec, args) < 0)
            return -1;
        if (print_argument(&out, &spec, args) < 0)
            return -1;
    }
    return out.count;
}

int my_printf(char const *format, ...)
{
    va_list args;
    int result;

    if (!format)
        return -1;
    va_start(args, format);
    result = print_format(format, &args);
    va_end(args);
    return result;
}
