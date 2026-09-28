#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <limits.h>
#include "../include/my.h"

Test(my_isneg, positive_number, .init = cr_redirect_stdout)
{
    int ret = my_isneg(42);

    cr_assert_eq(ret, 0);
    cr_assert_stdout_eq_str("P");
}

Test(my_isneg, zero_number, .init = cr_redirect_stdout)
{
    int ret = my_isneg(0);

    cr_assert_eq(ret, 0);
    cr_assert_stdout_eq_str("P");
}

Test(my_isneg, negative_number, .init = cr_redirect_stdout)
{
    int ret = my_isneg(-42);

    cr_assert_eq(ret, 0);
    cr_assert_stdout_eq_str("N");
}

Test(my_isneg, max_int, .init = cr_redirect_stdout)
{
    int ret = my_isneg(INT_MAX);

    cr_assert_eq(ret, 0);
    cr_assert_stdout_eq_str("P");
}

Test(my_isneg, min_int, .init = cr_redirect_stdout)
{
    int ret = my_isneg(INT_MIN);

    cr_assert_eq(ret, 0);
    cr_assert_stdout_eq_str("N");
}
