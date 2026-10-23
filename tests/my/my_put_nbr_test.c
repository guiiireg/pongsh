#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <limits.h>
#include "my/my.h"

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
}

Test(my_put_nbr, prints_zero, .init = redirect_all_stdout)
{
    my_put_nbr(0);
    cr_assert_stdout_eq_str("0");
}

Test(my_put_nbr, prints_positive_number, .init = redirect_all_stdout)
{
    my_put_nbr(42);
    cr_assert_stdout_eq_str("42");
}

Test(my_put_nbr, prints_negative_number, .init = redirect_all_stdout)
{
    my_put_nbr(-42);
    cr_assert_stdout_eq_str("-42");
}

Test(my_put_nbr, prints_int_max, .init = redirect_all_stdout)
{
    my_put_nbr(INT_MAX);
    cr_assert_stdout_eq_str("2147483647");
}

Test(my_put_nbr, prints_int_min, .init = redirect_all_stdout)
{
    my_put_nbr(INT_MIN);
    cr_assert_stdout_eq_str("-2147483648");
}
