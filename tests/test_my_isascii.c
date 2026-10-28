#include <criterion/criterion.h>
#include "my.h"

Test(my_isascii, in_range)
{
    cr_assert_eq(my_isascii(0), 1);
    cr_assert_eq(my_isascii(127), 1);
    cr_assert_eq(my_isascii('a'), 1);
}

Test(my_isascii, out_of_range)
{
    cr_assert_eq(my_isascii(128), 0);
    cr_assert_eq(my_isascii(255), 0);
    cr_assert_eq(my_isascii(-1), 0);
}
