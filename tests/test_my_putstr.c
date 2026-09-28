#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/my.h"

Test(my_putstr, print_standard_string, .init = cr_redirect_stdout)
{
    int ret = my_putstr("Hello, World!");

    cr_assert_eq(ret, 0);
    cr_assert_stdout_eq_str("Hello, World!");
}

Test(my_putstr, print_empty_string, .init = cr_redirect_stdout)
{
    int ret = my_putstr("");

    cr_assert_eq(ret, 0);
    cr_assert_stdout_eq_str("");
}

Test(my_putstr, print_with_special_characters, .init = cr_redirect_stdout)
{
    int ret = my_putstr("Line 1\n\tLine 2\n!@#$");

    cr_assert_eq(ret, 0);
    cr_assert_stdout_eq_str("Line 1\n\tLine 2\n!@#$");
}
