#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <limits.h>
#include <stdio.h>

#include "my.h"

Test(my_printf, plain_text, .init = cr_redirect_stdout)
{
    cr_assert_eq(my_printf("Hello"), 5);
    cr_assert_stdout_eq_str("Hello");
}

Test(my_printf, empty_format, .init = cr_redirect_stdout)
{
    cr_assert_eq(my_printf(""), 0);
    cr_assert_stdout_eq_str("");
}

Test(my_printf, null_format)
{
    cr_assert_eq(my_printf(NULL), -1);
}

Test(my_printf, literal_percent, .init = cr_redirect_stdout)
{
    cr_assert_eq(my_printf("100%%"), 4);
    cr_assert_stdout_eq_str("100%");
}

Test(my_printf, multiple_literal_percent, .init = cr_redirect_stdout)
{
    cr_assert_eq(my_printf("%%x%%y%%"), 5);
    cr_assert_stdout_eq_str("%x%y%");
}

Test(my_printf, lone_percent_at_end, .init = cr_redirect_stdout)
{
    cr_assert_eq(my_printf("abc%"), 4);
    cr_assert_stdout_eq_str("abc%");
}

Test(my_printf, return_counts_bytes, .init = cr_redirect_stdout)
{
    cr_assert_eq(my_printf("pongsh\n"), 7);
    cr_assert_stdout_eq_str("pongsh\n");
}

Test(my_printf, char_conversion, .init = cr_redirect_stdout)
{
    cr_assert_eq(my_printf("%c%c%c", 'H', 'e', 'y'), 3);
    cr_assert_stdout_eq_str("Hey");
}

Test(my_printf, char_with_text, .init = cr_redirect_stdout)
{
    cr_assert_eq(my_printf("a%cb", 'X'), 3);
    cr_assert_stdout_eq_str("aXb");
}

Test(my_printf, string_conversion, .init = cr_redirect_stdout)
{
    cr_assert_eq(my_printf("Hello %s!", "world"), 12);
    cr_assert_stdout_eq_str("Hello world!");
}

Test(my_printf, string_null, .init = cr_redirect_stdout)
{
    cr_assert_eq(my_printf("%s", NULL), 6);
    cr_assert_stdout_eq_str("(null)");
}

Test(my_printf, string_empty, .init = cr_redirect_stdout)
{
    cr_assert_eq(my_printf("%s", ""), 0);
    cr_assert_stdout_eq_str("");
}

Test(my_printf, signed_basic, .init = cr_redirect_stdout)
{
    cr_assert_eq(my_printf("%d", 42), 2);
    cr_assert_stdout_eq_str("42");
}

Test(my_printf, signed_negative, .init = cr_redirect_stdout)
{
    cr_assert_eq(my_printf("%i", -42), 3);
    cr_assert_stdout_eq_str("-42");
}

Test(my_printf, signed_zero, .init = cr_redirect_stdout)
{
    cr_assert_eq(my_printf("%d", 0), 1);
    cr_assert_stdout_eq_str("0");
}

Test(my_printf, signed_int_min, .init = cr_redirect_stdout)
{
    cr_assert_eq(my_printf("%d", INT_MIN), 11);
    cr_assert_stdout_eq_str("-2147483648");
}

Test(my_printf, signed_int_max, .init = cr_redirect_stdout)
{
    cr_assert_eq(my_printf("%i", INT_MAX), 10);
    cr_assert_stdout_eq_str("2147483647");
}

Test(my_printf, unsigned_conversion, .init = cr_redirect_stdout)
{
    cr_assert_eq(my_printf("%u", 0u), 1);
    cr_assert_stdout_eq_str("0");
}

Test(my_printf, unsigned_max, .init = cr_redirect_stdout)
{
    cr_assert_eq(my_printf("%u", UINT_MAX), 10);
    cr_assert_stdout_eq_str("4294967295");
}

Test(my_printf, hexa_lowercase, .init = cr_redirect_stdout)
{
    cr_assert_eq(my_printf("%x", 255u), 2);
    cr_assert_stdout_eq_str("ff");
}

Test(my_printf, hexa_uppercase, .init = cr_redirect_stdout)
{
    cr_assert_eq(my_printf("%X", 255u), 2);
    cr_assert_stdout_eq_str("FF");
}

Test(my_printf, hexa_zero_and_max, .init = cr_redirect_stdout)
{
    cr_assert_eq(my_printf("%x %x", 0u, UINT_MAX), 10);
    cr_assert_stdout_eq_str("0 ffffffff");
}

Test(my_printf, octal_conversion, .init = cr_redirect_stdout)
{
    cr_assert_eq(my_printf("%o", 8u), 2);
    cr_assert_stdout_eq_str("10");
}

Test(my_printf, octal_zero, .init = cr_redirect_stdout)
{
    cr_assert_eq(my_printf("%o", 0u), 1);
    cr_assert_stdout_eq_str("0");
}

Test(my_printf, pointer_null, .init = cr_redirect_stdout)
{
    cr_assert_eq(my_printf("%p", NULL), 3);
    cr_assert_stdout_eq_str("0x0");
}

Test(my_printf, pointer_value, .init = cr_redirect_stdout)
{
    char expected[64];

    snprintf(expected, sizeof(expected), "addr=%p\n", (void *)0x1234);
    cr_assert_eq(my_printf("addr=%p\n", (void *)0x1234), 12);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf, matches_printf_mixed, .init = cr_redirect_stdout)
{
    char expected[64];

    snprintf(expected, sizeof(expected), "salut %s %d %x\n", "toi", 42, 255);
    cr_assert_eq(my_printf("salut %s %d %x\n", "toi", 42, 255), 16);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf, matches_printf_all_conversions, .init = cr_redirect_stdout)
{
    char expected[128];

    snprintf(expected, sizeof(expected),
        "%c%s|%d|%i|%u|%o|%x|%X", 'A', "str", -7, 7, 42u, 64u, 255u, 255u);
    cr_assert_eq(my_printf("%c%s|%d|%i|%u|%o|%x|%X",
        'A', "str", -7, 7, 42u, 64u, 255u, 255u), 22);
    cr_assert_stdout_eq_str(expected);
}
