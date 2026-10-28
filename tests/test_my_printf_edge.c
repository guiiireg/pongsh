#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <limits.h>
#include <stdio.h>

#include "my.h"

/*
** Phase 4: remaining edge cases from the Phase 0 checklist, each
** validated against the real printf when applicable.
*/

Test(my_printf, string_precision_zero, .init = cr_redirect_stdout)
{
    char expected[64];

    snprintf(expected, sizeof(expected), "[%.0s]", "hello");
    cr_assert_eq(my_printf("[%.0s]", "hello"), 2);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf, string_empty_with_width, .init = cr_redirect_stdout)
{
    char expected[64];

    snprintf(expected, sizeof(expected), "[%5s]", "");
    cr_assert_eq(my_printf("[%5s]", ""), 7);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf, string_null_truncated_by_precision, .init = cr_redirect_stdout)
{
    char *str = NULL;
    char expected[64];

    snprintf(expected, sizeof(expected), "[%.3s]", str);
    cr_assert_eq(my_printf("[%.3s]", str), 2);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf, char_null_byte_is_written_and_counted,
    .init = cr_redirect_stdout)
{
    FILE *out = cr_get_redirected_stdout();
    int bytes[4];
    int i = 0;

    cr_assert_eq(my_printf("a%cb", 0), 3);
    while (i < 4) {
        bytes[i] = fgetc(out);
        i += 1;
    }
    cr_assert_eq(bytes[0], 'a');
    cr_assert_eq(bytes[1], '\0');
    cr_assert_eq(bytes[2], 'b');
    cr_assert_eq(bytes[3], EOF);
}

Test(my_printf, percent_with_flags_is_literal, .init = cr_redirect_stdout)
{
    /* Non standard: the whole specifier is written literally. */
    cr_assert_eq(my_printf("%5%"), 3);
    cr_assert_stdout_eq_str("%5%");
}

Test(my_printf, all_conversions_total_return, .init = cr_redirect_stdout)
{
    char expected[128];
    int expected_len;

    expected_len = snprintf(expected, sizeof(expected),
        "%c|%s|%d|%i|%u|%o|%x|%X|%p|%%",
        'Z', "str", INT_MIN, 7, 3000000000u, 64u, 255u, 255u,
        (void *)0x42);
    cr_assert_eq(my_printf("%c|%s|%d|%i|%u|%o|%x|%X|%p|%%",
        'Z', "str", INT_MIN, 7, 3000000000u, 64u, 255u, 255u,
        (void *)0x42), expected_len);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf, width_applies_to_everything, .init = cr_redirect_stdout)
{
    char expected[128];
    int expected_len;

    expected_len = snprintf(expected, sizeof(expected),
        "[%3c][%6s][%5d][%#8x][%9p]", 'a', "hi", 42, 255u, (void *)0x12);
    cr_assert_eq(my_printf("[%3c][%6s][%5d][%#8x][%9p]",
        'a', "hi", 42, 255u, (void *)0x12), expected_len);
    cr_assert_stdout_eq_str(expected);
}

Test(my_printf, unknown_specifiers_are_literal, .init = cr_redirect_stdout)
{
    cr_assert_eq(my_printf("%q %w"), 5);
    cr_assert_stdout_eq_str("%q %w");
}
