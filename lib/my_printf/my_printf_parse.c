#include "../../include/my_printf_internal.h"

static unsigned int flag_for(char c)
{
    switch (c) {
        case '-':
            return PRINTF_LEFT;
        case '+':
            return PRINTF_PLUS;
        case ' ':
            return PRINTF_SPACE;
        case '#':
            return PRINTF_ALT;
        case '0':
            return PRINTF_ZERO;
        default:
            return 0;
    }
}

static printf_length_t read_pair(char const **format,
    printf_length_t single, printf_length_t pair)
{
    if ((*format)[0] == (*format)[1]) {
        *format += 2;
        return pair;
    }
    (*format)++;
    return single;
}

static printf_length_t read_length(char const **format)
{
    if (**format == 'h')
        return read_pair(format, PRINTF_H, PRINTF_HH);
    if (**format == 'l')
        return read_pair(format, PRINTF_L, PRINTF_LL);
    if (**format == 'j') {
        (*format)++;
        return PRINTF_J;
    }
    return PRINTF_DEFAULT;
}

int my_printf_parse(char const **format, printf_spec_t *spec, va_list *args)
{
    unsigned int flag = flag_for(**format);

    *spec = (printf_spec_t){.precision = -1};
    while (flag) {
        spec->flags |= flag;
        (*format)++;
        flag = flag_for(**format);
    }
    if (my_printf_read_dimensions(format, spec, args) < 0)
        return -1;
    spec->length = read_length(format);
    if (!**format)
        return -1;
    spec->type = **format;
    (*format)++;
    return 0;
}
