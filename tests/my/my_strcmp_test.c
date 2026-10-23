#include <criterion/criterion.h>
#include "../include/my.h"

Test(my_strcmp, equal_strings_return_zero)
{
    cr_assert_eq(my_strcmp("abc", "abc"), 0);
}

Test(my_strcmp, empty_strings_return_zero)
{
    cr_assert_eq(my_strcmp("", ""), 0);
}

Test(my_strcmp, first_shorter_returns_negative)
{
    cr_assert_lt(my_strcmp("ab", "abc"), 0);
}

Test(my_strcmp, first_longer_returns_positive)
{
    cr_assert_gt(my_strcmp("abc", "ab"), 0);
}

Test(my_strcmp, different_char_returns_correct_sign)
{
    cr_assert_lt(my_strcmp("abc", "abd"), 0);
    cr_assert_gt(my_strcmp("abd", "abc"), 0);
}
