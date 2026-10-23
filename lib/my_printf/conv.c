#include "conv.h"
#include <stddef.h>

/**
 * @brief Write a %c conversion into the output buffer.
 * @param ctx: output context.
 * @param ap: variadic arguments cursor.
 */
void conv_char(out_ctx_t *ctx, va_list *ap)
{
    out_putchar(ctx, (char)va_arg(*ap, int));
}

/**
 * @brief Write a %s conversion into the output buffer.
 * @param ctx: output context.
 * @param ap: variadic arguments cursor.
 */
void conv_str(out_ctx_t *ctx, va_list *ap)
{
    char *str = va_arg(*ap, char *);

    if (str == NULL)
        str = "(null)";
    out_putstr(ctx, str);
}

/**
 * @brief Write the decimal digits of a non-negative number.
 * @param ctx: output context.
 * @param value: number to write, never negative.
 */
static void print_digits(out_ctx_t *ctx, long long value)
{
    if (value < 10) {
        out_putchar(ctx, (char)('0' + value));
        return;
    }
    print_digits(ctx, value / 10);
    out_putchar(ctx, (char)('0' + value % 10));
}

/**
 * @brief Write a %d or %i conversion into the output buffer.
 * @param ctx: output context.
 * @param ap: variadic arguments cursor.
 */
void conv_int(out_ctx_t *ctx, va_list *ap)
{
    long long value = va_arg(*ap, int);

    if (value < 0) {
        out_putchar(ctx, '-');
        value = -value;
    }
    print_digits(ctx, value);
}
