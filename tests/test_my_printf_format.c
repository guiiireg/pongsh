#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <limits.h>
#include <stdio.h>

#include "my.h"

/*
** Phase 3: every formatting test is checked against the real printf,
** both the output and the returned byte count.
*/

static void assert_same(char const *format, int value)
{
    char expected[64];
    int expected_len = snprintf(expected, sizeof(expected), format, value);

    cr_assert_eq(my_printf(format, value), expected_len);
    cr_assert_stdout_eq_str(expected);
}

static void assert_same_str(char const *format, char const *value)
{
    char expected[64];
    int expected_len = snprintf(expected, sizeof(expected), format, value);

    cr_assert_eq(my_printf(format, value), expected_len);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf, width_basic, .init = cr_redirect_stdout)
{
    assert_same("%5d", 42);
}

Test(my_printf, width_smaller_than_value, .init = cr_redirect_stdout)
{
    assert_same("%2d", 42);
}

Test(my_printf, width_left_aligned, .init = cr_redirect_stdout)
{
    char expected[64];

    snprintf(expected, sizeof(expected), "%-5d|", 42);
    cr_assert_eq(my_printf("%-5d|", 42), 6);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf, zero_flag, .init = cr_redirect_stdout)
{
    assert_same("%05d", 42);
}

Test(my_printf, zero_ignored_with_left, .init = cr_redirect_stdout)
{
    /* The 0 flag is ignored when the - flag is present. */
    cr_assert_eq(my_printf("[%-05d]", 42), 7);
    cr_assert_stdout_eq_str("[42   ]");
}

Test(my_printf, plus_flag, .init = cr_redirect_stdout)
{
    assert_same("%+d", 42);
}

Test(my_printf, space_flag, .init = cr_redirect_stdout)
{
    assert_same("% d", 42);
}

Test(my_printf, plus_overrides_space, .init = cr_redirect_stdout)
{
    assert_same("% +d", 42);
}

Test(my_printf, space_ignored_on_negative, .init = cr_redirect_stdout)
{
    assert_same("% d", -42);
}

Test(my_printf, precision_digits, .init = cr_redirect_stdout)
{
    assert_same("%.5d", 42);
}

Test(my_printf, precision_zero_value_zero, .init = cr_redirect_stdout)
{
    assert_same("%.0d", 0);
}

Test(my_printf, width_precision_zero_value_zero, .init = cr_redirect_stdout)
{
    assert_same("%5.0d", 0);
}

Test(my_printf, precision_overrides_zero_flag, .init = cr_redirect_stdout)
{
    assert_same("%05.3d", 42);
}

Test(my_printf, int_min_with_zero_flag, .init = cr_redirect_stdout)
{
    assert_same("%011d", INT_MIN);
}

Test(my_printf, int_min_with_plus_flag, .init = cr_redirect_stdout)
{
    assert_same("%+d", INT_MIN);
}

Test(my_printf, hash_octal, .init = cr_redirect_stdout)
{
    assert_same("%#o", 8);
}

Test(my_printf, hash_octal_zero, .init = cr_redirect_stdout)
{
    assert_same("%#o", 0);
}

Test(my_printf, hash_octal_precision, .init = cr_redirect_stdout)
{
    assert_same("%#.5o", 8);
}

Test(my_printf, hash_hexa_lowercase, .init = cr_redirect_stdout)
{
    assert_same("%#x", 255);
}

Test(my_printf, hash_hexa_uppercase, .init = cr_redirect_stdout)
{
    assert_same("%#X", 255);
}

Test(my_printf, hash_hexa_zero, .init = cr_redirect_stdout)
{
    assert_same("%#x", 0);
}

Test(my_printf, zeros_after_hash_prefix, .init = cr_redirect_stdout)
{
    assert_same("%#08x", 255);
}

Test(my_printf, star_width, .init = cr_redirect_stdout)
{
    char expected[64];

    snprintf(expected, sizeof(expected), "[%*d]", 5, 42);
    cr_assert_eq(my_printf("[%*d]", 5, 42), 7);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf, star_width_negative, .init = cr_redirect_stdout)
{
    char expected[64];

    snprintf(expected, sizeof(expected), "[%*d]", -5, 42);
    cr_assert_eq(my_printf("[%*d]", -5, 42), 7);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf, star_precision, .init = cr_redirect_stdout)
{
    char expected[64];

    snprintf(expected, sizeof(expected), "[%.*d]", 5, 42);
    cr_assert_eq(my_printf("[%.*d]", 5, 42), 7);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf, star_precision_negative_is_omitted, .init = cr_redirect_stdout)
{
    char expected[64];

    snprintf(expected, sizeof(expected), "[%.*d]", -1, 42);
    cr_assert_eq(my_printf("[%.*d]", -1, 42), 4);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf, string_precision_truncates, .init = cr_redirect_stdout)
{
    assert_same_str("%.3s", "hello");
}

Test(my_printf, string_width_precision, .init = cr_redirect_stdout)
{
    assert_same_str("%8.3s|", "hello");
}

Test(my_printf, string_left_aligned, .init = cr_redirect_stdout)
{
    assert_same_str("[%-6s]", "hi");
}

Test(my_printf, string_null_with_width, .init = cr_redirect_stdout)
{
    assert_same_str("[%10s]", NULL);
}

Test(my_printf, char_width, .init = cr_redirect_stdout)
{
    char expected[64];

    snprintf(expected, sizeof(expected), "[%3c]", 'x');
    cr_assert_eq(my_printf("[%3c]", 'x'), 5);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf, char_left_aligned, .init = cr_redirect_stdout)
{
    char expected[64];

    snprintf(expected, sizeof(expected), "[%-3c]", 'x');
    cr_assert_eq(my_printf("[%-3c]", 'x'), 5);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf, pointer_width, .init = cr_redirect_stdout)
{
    /* Deviation from glibc, documented in the plan: NULL prints 0x0. */
    cr_assert_eq(my_printf("[%8p]", NULL), 10);
    cr_assert_stdout_eq_str("[     0x0]");
}

Test(my_printf, pointer_left_aligned, .init = cr_redirect_stdout)
{
    char expected[64];

    snprintf(expected, sizeof(expected), "[%-8p]", (void *)0x12);
    cr_assert_eq(my_printf("[%-8p]", (void *)0x12), 10);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf, mixed_all_formatting, .init = cr_redirect_stdout)
{
    char expected[64];

    snprintf(expected, sizeof(expected), "[%-+8.5d]", 42);
    cr_assert_eq(my_printf("[%-+8.5d]", 42), 10);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf, unknown_specifier_with_flags, .init = cr_redirect_stdout)
{
    cr_assert_eq(my_printf("[%5q]", 42), 5);
    cr_assert_stdout_eq_str("[%5q]");
}
