#include "out.h"
#include "../../include/my.h"
#include <stdlib.h>
#include <unistd.h>

/**
 * @brief Initialize a growing output buffer.
 * @param ctx: context to initialize.
 */
void out_init(out_ctx_t *ctx)
{
    ctx->cap = OUT_INITIAL_CAP;
    ctx->len = 0;
    ctx->error = 0;
    ctx->buf = malloc(sizeof(char) * ctx->cap);
    if (ctx->buf == NULL)
        ctx->error = 1;
}

/**
 * @brief Double the buffer capacity, preserving its content.
 * @param ctx: output context.
 * @return 0 on success, -1 on allocation failure.
 */
static int out_grow(out_ctx_t *ctx)
{
    char *new_buf = malloc(sizeof(char) * (ctx->cap * 2));

    if (new_buf == NULL)
        return -1;
    my_memcpy(new_buf, ctx->buf, ctx->len);
    free(ctx->buf);
    ctx->buf = new_buf;
    ctx->cap *= 2;
    return 0;
}

/**
 * @brief Append a single character, growing the buffer if needed.
 * @param ctx: output context.
 * @param c: character to append.
 */
void out_putchar(out_ctx_t *ctx, char c)
{
    if (ctx->error == 1)
        return;
    if (ctx->len == ctx->cap && out_grow(ctx) == -1) {
        ctx->error = 1;
        return;
    }
    ctx->buf[ctx->len] = c;
    ctx->len += 1;
}

/**
 * @brief Write the whole buffer to stdout in one call, then release it.
 * @param ctx: output context, consumed by the call.
 */
void out_flush(out_ctx_t *ctx)
{
    int written = 0;
    int count = 0;

    while (ctx->error == 0 && written < ctx->len) {
        count = write(1, ctx->buf + written, ctx->len - written);
        if (count == -1)
            ctx->error = 1;
        else
            written += count;
    }
    free(ctx->buf);
    ctx->buf = NULL;
    ctx->len = 0;
    ctx->cap = 0;
}
