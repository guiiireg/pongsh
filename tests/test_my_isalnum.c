#include <criterion/criterion.h>
#include "my.h"

Test(my_isalnum, letters)
{
    cr_assert_eq(my_isalnum('a'), 1);
    cr_assert_eq(my_isalnum('Z'), 1);
}

Test(my_isalnum, digits)
{
    cr_assert_eq(my_isalnum('0'), 1);
    cr_assert_eq(my_isalnum('9'), 1);
}

Test(my_isalnum, non_alphanumeric)
{
    cr_assert_eq(my_isalnum('!'), 0);
    cr_assert_eq(my_isalnum(' '), 0);
}
