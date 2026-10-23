#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <limits.h>
#include <stdio.h>
#include "../../include/my_printf.h"

Test(my_printf, writes_plain_text)
{
    char got[64] = {0};

    cr_redirect_stdout();
    cr_assert_eq(my_printf("hello world"), 11);
    fgets(got, sizeof(got), cr_get_redirected_stdout());
    cr_assert_str_eq(got, "hello world");
}

Test(my_printf, writes_empty_format)
{
    char got[16] = {0};

    cr_redirect_stdout();
    cr_assert_eq(my_printf(""), 0);
    fgets(got, sizeof(got), cr_get_redirected_stdout());
    cr_assert_str_eq(got, "");
}

Test(my_printf, writes_string_specifier)
{
    char got[64] = {0};

    cr_redirect_stdout();
    my_printf("hello %s!", "world");
    fgets(got, sizeof(got), cr_get_redirected_stdout());
    cr_assert_str_eq(got, "hello world!");
}

Test(my_printf, handles_null_string)
{
    char got[16] = {0};

    cr_redirect_stdout();
    my_printf("%s", NULL);
    fgets(got, sizeof(got), cr_get_redirected_stdout());
    cr_assert_str_eq(got, "(null)");
}

Test(my_printf, handles_empty_string)
{
    char got[16] = {0};

    cr_redirect_stdout();
    my_printf("[%s]", "");
    fgets(got, sizeof(got), cr_get_redirected_stdout());
    cr_assert_str_eq(got, "[]");
}

Test(my_printf, writes_char_specifier)
{
    char got[16] = {0};

    cr_redirect_stdout();
    my_printf("%c%c%c", 'a', 'b', 'c');
    fgets(got, sizeof(got), cr_get_redirected_stdout());
    cr_assert_str_eq(got, "abc");
}

Test(my_printf, writes_int_specifier)
{
    char got[16] = {0};

    cr_redirect_stdout();
    my_printf("%d", 42);
    fgets(got, sizeof(got), cr_get_redirected_stdout());
    cr_assert_str_eq(got, "42");
}

Test(my_printf, writes_i_like_d)
{
    char got[16] = {0};

    cr_redirect_stdout();
    my_printf("%i", 123);
    fgets(got, sizeof(got), cr_get_redirected_stdout());
    cr_assert_str_eq(got, "123");
}

Test(my_printf, handles_negative_int)
{
    char got[16] = {0};

    cr_redirect_stdout();
    my_printf("%d", -17);
    fgets(got, sizeof(got), cr_get_redirected_stdout());
    cr_assert_str_eq(got, "-17");
}

Test(my_printf, handles_zero_int)
{
    char got[16] = {0};

    cr_redirect_stdout();
    my_printf("%d", 0);
    fgets(got, sizeof(got), cr_get_redirected_stdout());
    cr_assert_str_eq(got, "0");
}

Test(my_printf, handles_int_min)
{
    char got[16] = {0};

    cr_redirect_stdout();
    my_printf("%d", INT_MIN);
    fgets(got, sizeof(got), cr_get_redirected_stdout());
    cr_assert_str_eq(got, "-2147483648");
}

Test(my_printf, writes_literal_percent)
{
    char got[16] = {0};

    cr_redirect_stdout();
    my_printf("100%%");
    fgets(got, sizeof(got), cr_get_redirected_stdout());
    cr_assert_str_eq(got, "100%");
}

Test(my_printf, mixes_specifiers)
{
    char got[64] = {0};

    cr_redirect_stdout();
    my_printf("%s=%d,%c", "a", 7, 'z');
    fgets(got, sizeof(got), cr_get_redirected_stdout());
    cr_assert_str_eq(got, "a=7,z");
}

Test(my_printf, counts_return_value)
{
    cr_redirect_stdout();
    cr_assert_eq(my_printf("%d-%s", 12, "ab"), 5);
}

Test(my_printf, echoes_unknown_specifier)
{
    char got[16] = {0};

    cr_redirect_stdout();
    my_printf("%q");
    fgets(got, sizeof(got), cr_get_redirected_stdout());
    cr_assert_str_eq(got, "%q");
}

Test(my_printf, ignores_trailing_percent)
{
    char got[16] = {0};

    cr_redirect_stdout();
    my_printf("abc%");
    fgets(got, sizeof(got), cr_get_redirected_stdout());
    cr_assert_str_eq(got, "abc");
}
