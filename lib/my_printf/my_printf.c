#include "../../include/my_printf.h"
#include "conv.h"
#include "out.h"
#include <stdarg.h>

/**
 * @brief Walk the format string, writing literals and handling specifiers.
 * @param ctx: output context.
 * @param format: format string to walk.
 * @param ap: variadic arguments cursor.
 */
static void parse_format(out_ctx_t *ctx, const char *format, va_list *ap)
{
    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] != '%') {
            out_putchar(ctx, format[i]);
            continue;
        }
        handle_spec(ctx, format, &i, ap);
    }
}

/**
 * @brief Write a formatted string to stdout.
 * @param format: format string with conversion specifiers.
 * @return Number of characters written, -1 on error.
 */
int my_printf(const char *format, ...)
{
    out_ctx_t ctx;
    int written = 0;
    va_list ap;

    out_init(&ctx);
    if (ctx.error == 0) {
        va_start(ap, format);
        parse_format(&ctx, format, &ap);
        va_end(ap);
        written = ctx.len;
    }
    out_flush(&ctx);
    if (ctx.error == 1)
        written = -1;
    return written;
}
