#include <criterion/criterion.h>
#include "../include/my.h"

Test(my_strncmp, equal_prefix_returns_zero)
{
    cr_assert_eq(my_strncmp("abcdef", "abcxyz", 3), 0);
}

Test(my_strncmp, difference_inside_n_returns_correct_sign)
{
    cr_assert_lt(my_strncmp("abcdef", "abcxyz", 4), 0);
    cr_assert_gt(my_strncmp("abcxyz", "abcdef", 4), 0);
}

Test(my_strncmp, zero_n_returns_zero)
{
    cr_assert_eq(my_strncmp("abc", "xyz", 0), 0);
}

Test(my_strncmp, fully_equal_strings_return_zero)
{
    cr_assert_eq(my_strncmp("abc", "abc", 3), 0);
}

Test(my_strncmp, shorter_string_compared_with_null_byte)
{
    cr_assert_lt(my_strncmp("ab", "abc", 3), 0);
    cr_assert_gt(my_strncmp("abc", "ab", 3), 0);
}
