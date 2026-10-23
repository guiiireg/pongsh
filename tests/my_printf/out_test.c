#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdio.h>
#include <string.h>
#include "../../include/my.h"
#include "../../lib/my_printf/out.h"

Test(out, init_allocates_empty_buffer)
{
    out_ctx_t ctx;

    out_init(&ctx);
    cr_assert_not_null(ctx.buf);
    cr_assert_eq(ctx.len, 0);
    cr_assert_gt(ctx.cap, 0);
    cr_assert_eq(ctx.error, 0);
    out_free(&ctx);
}

Test(out, putchar_stores_characters_in_order)
{
    out_ctx_t ctx;

    out_init(&ctx);
    out_putchar(&ctx, 'a');
    out_putchar(&ctx, 'b');
    out_putchar(&ctx, 'c');
    cr_assert_eq(ctx.len, 3);
    cr_assert_eq(my_memcmp(ctx.buf, "abc", 3), 0);
    out_free(&ctx);
}

Test(out, putstr_appends_whole_string)
{
    out_ctx_t ctx;

    out_init(&ctx);
    out_putstr(&ctx, "hello");
    cr_assert_eq(ctx.len, 5);
    cr_assert_eq(my_memcmp(ctx.buf, "hello", 5), 0);
    out_free(&ctx);
}

Test(out, putstr_handles_empty_string)
{
    out_ctx_t ctx;

    out_init(&ctx);
    out_putstr(&ctx, "");
    cr_assert_eq(ctx.len, 0);
    out_free(&ctx);
}

Test(out, growth_preserves_content_across_reallocation)
{
    out_ctx_t ctx;
    char expected[201];

    memset(expected, 'x', 200);
    expected[200] = '\0';
    out_init(&ctx);
    out_putstr(&ctx, expected);
    cr_assert_eq(ctx.len, 200);
    cr_assert_gt(ctx.cap, 200);
    cr_assert_eq(my_memcmp(ctx.buf, expected, 200), 0);
    out_free(&ctx);
}

Test(out, flush_writes_content_and_resets_length)
{
    out_ctx_t ctx;
    char got[64] = {0};

    out_init(&ctx);
    out_putstr(&ctx, "hello buffer");
    cr_redirect_stdout();
    out_flush(&ctx);
    cr_assert_eq(ctx.len, 0);
    fgets(got, sizeof(got), cr_get_redirected_stdout());
    cr_assert_str_eq(got, "hello buffer");
    out_free(&ctx);
}

Test(out, flush_after_error_writes_nothing)
{
    out_ctx_t ctx;
    char got[64] = {0};

    out_init(&ctx);
    out_putstr(&ctx, "leaked content");
    ctx.error = 1;
    cr_redirect_stdout();
    out_flush(&ctx);
    fgets(got, sizeof(got), cr_get_redirected_stdout());
    cr_assert_str_eq(got, "");
    out_free(&ctx);
}
