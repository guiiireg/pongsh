#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdio.h>
#include <string.h>
#include "my/my.h"
#include "my_printf/internal/out.h"

Test(out, init_allocates_empty_buffer)
{
    out_ctx_t ctx;

    out_init(&ctx);
    cr_assert_not_null(ctx.buf);
    cr_assert_eq(ctx.len, 0);
    cr_assert_gt(ctx.cap, 0);
    cr_assert_eq(ctx.error, 0);
    out_flush(&ctx);
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
    out_flush(&ctx);
}

Test(out, growth_preserves_content_across_reallocation)
{
    out_ctx_t ctx;
    char expected[201];

    memset(expected, 'x', 200);
    expected[200] = '\0';
    out_init(&ctx);
    for (int i = 0; i < 200; i++)
        out_putchar(&ctx, 'x');
    cr_assert_eq(ctx.len, 200);
    cr_assert_gt(ctx.cap, 200);
    cr_assert_eq(my_memcmp(ctx.buf, expected, 200), 0);
    out_flush(&ctx);
}

Test(out, flush_writes_content_and_releases_buffer)
{
    out_ctx_t ctx;
    char got[16] = {0};

    out_init(&ctx);
    for (int i = 0; i < 5; i++)
        out_putchar(&ctx, (char)('a' + i));
    cr_redirect_stdout();
    out_flush(&ctx);
    cr_assert_eq(ctx.len, 0);
    cr_assert_eq(ctx.cap, 0);
    cr_assert_null(ctx.buf);
    fgets(got, sizeof(got), cr_get_redirected_stdout());
    cr_assert_str_eq(got, "abcde");
}

Test(out, flush_after_error_writes_nothing_and_releases)
{
    out_ctx_t ctx;
    char got[16] = {0};

    out_init(&ctx);
    out_putchar(&ctx, 'x');
    ctx.error = 1;
    cr_redirect_stdout();
    out_flush(&ctx);
    cr_assert_null(ctx.buf);
    fgets(got, sizeof(got), cr_get_redirected_stdout());
    cr_assert_str_eq(got, "");
}
