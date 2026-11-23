#include "my_printf_internal.h"

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

static enum printf_length read_length(char const **format)
{
    char c = **format;

    if (c != 'h' && c != 'l' && c != 'j')
        return PRINTF_DEFAULT;
    (*format)++;
    if (c == 'j')
        return PRINTF_J;
    if (**format == c) {
        (*format)++;
        if (c == 'h')
            return PRINTF_HH;
        return PRINTF_LL;
    }
    if (c == 'h')
        return PRINTF_H;
    return PRINTF_L;
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
