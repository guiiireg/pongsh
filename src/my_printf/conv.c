#include "internal/conv.h"
#include <stddef.h>

/**
 * @brief Write the digits of a non-negative number in the given base.
 */
static void print_base(out_ctx_t *ctx, unsigned long long value, const char *base, int base_len)
{
    if (value < (unsigned long long)base_len) {
        out_putchar(ctx, base[value]);
        return;
    }
    print_base(ctx, value / base_len, base, base_len);
    out_putchar(ctx, base[value % base_len]);
}

/**
 * @brief Write a %c, %s or %p conversion into the output buffer.
 */
static void conv_text(out_ctx_t *ctx, va_list *ap, const conv_t *conv)
{
    char *str = NULL;
    int i = 0;

    if (conv->kind == KIND_CHAR) {
        out_putchar(ctx, (char)va_arg(*ap, int));
        return;
    }
    str = va_arg(*ap, char *);
    if (str == NULL)
        str = conv->kind == KIND_PTR ? "(nil)" : "(null)";
    else if (conv->kind == KIND_PTR) {
        out_putchar(ctx, '0');
        out_putchar(ctx, 'x');
        print_base(ctx, (unsigned long long)(size_t)str, conv->base, conv->base_len);
        return;
    }
    for (i = 0; str[i] != '\0'; i++)
        out_putchar(ctx, str[i]);
}

/**
 * @brief Write a %d, %i, %u, %x, %X or %o conversion into the buffer.
 */
static void conv_num(out_ctx_t *ctx, va_list *ap, const conv_t *conv)
{
    unsigned long long value = va_arg(*ap, unsigned int);

    if (conv->sign != 0 && (int)value < 0) {
        out_putchar(ctx, '-');
        value = -(long long)(int)value;
    }
    print_base(ctx, value, conv->base, conv->base_len);
}

static const conv_t CONVERSIONS[] = {
    {'c', KIND_CHAR, 0, NULL, 0, conv_text},
    {'s', KIND_STR, 0, NULL, 0, conv_text},
    {'d', KIND_NUM, 1, "0123456789", 10, conv_num},
    {'i', KIND_NUM, 1, "0123456789", 10, conv_num},
    {'u', KIND_NUM, 0, "0123456789", 10, conv_num},
    {'x', KIND_NUM, 0, "0123456789abcdef", 16, conv_num},
    {'X', KIND_NUM, 0, "0123456789ABCDEF", 16, conv_num},
    {'o', KIND_NUM, 0, "01234567", 8, conv_num},
    {'p', KIND_PTR, 0, "0123456789abcdef", 16, conv_text},
    {'\0', 0, 0, NULL, 0, NULL}
};

/**
 * @brief Handle the specifier starting at format[*i], expected to be '%'.
 * @param i: index of the '%', advanced past the whole specifier.
 */
void handle_spec(out_ctx_t *ctx, const char *format, int *i, va_list *ap)
{
    char spec = format[*i + 1];

    if (spec == '\0')
        return;
    *i += 1;
    if (spec == '%') {
        out_putchar(ctx, '%');
        return;
    }
    for (int j = 0; CONVERSIONS[j].spec != '\0'; j++) {
        if (CONVERSIONS[j].spec == spec) {
            CONVERSIONS[j].fn(ctx, ap, &CONVERSIONS[j]);
            return;
        }
    }
    out_putchar(ctx, '%');
    out_putchar(ctx, spec);
}
