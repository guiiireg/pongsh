#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <limits.h>
#include <stdio.h>
#include "my_printf/my_printf.h"
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

Test(my_printf, writes_uint_specifier)
{
    char got[16] = {0};

    cr_redirect_stdout();
    my_printf("%u", 42u);
    fgets(got, sizeof(got), cr_get_redirected_stdout());
    cr_assert_str_eq(got, "42");
}

Test(my_printf, handles_uint_max)
{
    char got[16] = {0};

    cr_redirect_stdout();
    my_printf("%u", UINT_MAX);
    fgets(got, sizeof(got), cr_get_redirected_stdout());
    cr_assert_str_eq(got, "4294967295");
}

Test(my_printf, reinterprets_negative_int_as_uint)
{
    char got[16] = {0};

    cr_redirect_stdout();
    my_printf("%u", -1);
    fgets(got, sizeof(got), cr_get_redirected_stdout());
    cr_assert_str_eq(got, "4294967295");
}

Test(my_printf, writes_hex_lower)
{
    char got[16] = {0};

    cr_redirect_stdout();
    my_printf("%x", 255);
    fgets(got, sizeof(got), cr_get_redirected_stdout());
    cr_assert_str_eq(got, "ff");
}

Test(my_printf, writes_hex_upper)
{
    char got[16] = {0};

    cr_redirect_stdout();
    my_printf("%X", 255);
    fgets(got, sizeof(got), cr_get_redirected_stdout());
    cr_assert_str_eq(got, "FF");
}

Test(my_printf, writes_octal)
{
    char got[16] = {0};

    cr_redirect_stdout();
    my_printf("%o", 64);
    fgets(got, sizeof(got), cr_get_redirected_stdout());
    cr_assert_str_eq(got, "100");
}

Test(my_printf, handles_zero_hex)
{
    char got[16] = {0};

    cr_redirect_stdout();
    my_printf("%x", 0);
    fgets(got, sizeof(got), cr_get_redirected_stdout());
    cr_assert_str_eq(got, "0");
}

Test(my_printf, writes_pointer_specifier)
{
    char got[64] = {0};
    char expected[64] = {0};
    int value = 0;

    cr_redirect_stdout();
    my_printf("%p", &value);
    snprintf(expected, sizeof(expected), "%p", &value);
    fgets(got, sizeof(got), cr_get_redirected_stdout());
    cr_assert_str_eq(got, expected);
}

Test(my_printf, handles_null_pointer)
{
    char got[16] = {0};

    cr_redirect_stdout();
    my_printf("%p", NULL);
    fgets(got, sizeof(got), cr_get_redirected_stdout());
    cr_assert_str_eq(got, "(nil)");
}
