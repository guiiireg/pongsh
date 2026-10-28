#include <criterion/criterion.h>
#include "my.h"

Test(my_isupper, uppercase_letters)
{
    cr_assert_eq(my_isupper('A'), 1);
    cr_assert_eq(my_isupper('Z'), 1);
}

Test(my_isupper, non_uppercase)
{
    cr_assert_eq(my_isupper('a'), 0);
    cr_assert_eq(my_isupper('['), 0);
    cr_assert_eq(my_isupper('@'), 0);
}
