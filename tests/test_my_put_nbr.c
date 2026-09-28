#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <limits.h>
#include "../include/my.h"

Test(my_put_nbr, positive_number, .init = cr_redirect_stdout)
{
    int ret = my_put_nbr(42);

    cr_assert_eq(ret, 0);
    cr_assert_stdout_eq_str("42");
}

Test(my_put_nbr, single_digit_positive, .init = cr_redirect_stdout)
{
    int ret = my_put_nbr(7);

    cr_assert_eq(ret, 0);
    cr_assert_stdout_eq_str("7");
}

Test(my_put_nbr, zero_number, .init = cr_redirect_stdout)
{
    int ret = my_put_nbr(0);

    cr_assert_eq(ret, 0);
    cr_assert_stdout_eq_str("0");
}

Test(my_put_nbr, negative_number, .init = cr_redirect_stdout)
{
    int ret = my_put_nbr(-42);

    cr_assert_eq(ret, 0);
    cr_assert_stdout_eq_str("-42");
}

Test(my_put_nbr, single_digit_negative, .init = cr_redirect_stdout)
{
    int ret = my_put_nbr(-9);

    cr_assert_eq(ret, 0);
    cr_assert_stdout_eq_str("-9");
}

Test(my_put_nbr, max_int, .init = cr_redirect_stdout)
{
    int ret = my_put_nbr(INT_MAX);

    cr_assert_eq(ret, 0);
    cr_assert_stdout_eq_str("2147483647");
}

Test(my_put_nbr, min_int, .init = cr_redirect_stdout)
{
    int ret = my_put_nbr(INT_MIN);

    cr_assert_eq(ret, 0);
    cr_assert_stdout_eq_str("-2147483648");
}
