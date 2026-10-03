#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/my_printf.h"

Test(my_printf, null_format)
{
    int ret = my_printf(NULL);

    cr_assert_eq(ret, -1);
}

Test(my_printf, empty_format, .init = cr_redirect_stdout)
{
    int ret = my_printf("");

    cr_assert_eq(ret, 0);
    cr_assert_stdout_eq_str("");
}

Test(my_printf, simple_string, .init = cr_redirect_stdout)
{
    int ret = my_printf("Bonjour\n");

    cr_assert_eq(ret, 8);
    cr_assert_stdout_eq_str("Bonjour\n");
}

Test(my_printf, single_percent_escape, .init = cr_redirect_stdout)
{
    int ret = my_printf("%%");

    cr_assert_eq(ret, 1);
    cr_assert_stdout_eq_str("%");
}

Test(my_printf, percent_with_text, .init = cr_redirect_stdout)
{
    int ret = my_printf("100%%\n");

    cr_assert_eq(ret, 5);
    cr_assert_stdout_eq_str("100%\n");
}

Test(my_printf, four_percents, .init = cr_redirect_stdout)
{
    int ret = my_printf("%%%%");

    cr_assert_eq(ret, 2);
    cr_assert_stdout_eq_str("%%");
}

Test(my_printf, percent_in_between, .init = cr_redirect_stdout)
{
    int ret = my_printf("a%%b");

    cr_assert_eq(ret, 3);
    cr_assert_stdout_eq_str("a%b");
}

Test(my_printf, trailing_percent, .init = cr_redirect_stdout)
{
    int ret = my_printf("abc%");

    cr_assert_eq(ret, 3);
    cr_assert_stdout_eq_str("abc");
}

Test(my_printf, only_trailing_percent, .init = cr_redirect_stdout)
{
    int ret = my_printf("%");

    cr_assert_eq(ret, 0);
    cr_assert_stdout_eq_str("");
}
