#include <criterion/criterion.h>
#include "my.h"

Test(my_isdigit, digits)
{
    cr_assert_eq(my_isdigit('0'), 1);
    cr_assert_eq(my_isdigit('5'), 1);
    cr_assert_eq(my_isdigit('9'), 1);
}

Test(my_isdigit, boundaries)
{
    cr_assert_eq(my_isdigit('/'), 0);
    cr_assert_eq(my_isdigit(':'), 0);
}

Test(my_isdigit, non_digit)
{
    cr_assert_eq(my_isdigit('a'), 0);
    cr_assert_eq(my_isdigit(' '), 0);
}
