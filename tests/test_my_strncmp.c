#include <criterion/criterion.h>
#include "../include/my.h"

Test(my_strncmp, identical_strings)
{
    cr_assert_eq(my_strncmp("Hello", "Hello", 5), 0);
    cr_assert_eq(my_strncmp("Hello", "Hello", 10), 0);
    cr_assert_eq(my_strncmp("", "", 3), 0);
}

Test(my_strncmp, matching_prefix_different_after_n)
{
    cr_assert_eq(my_strncmp("HelloWorld", "HelloThere", 5), 0);
    cr_assert_gt(my_strncmp("HelloWorld", "HelloThere", 6), 0);
    cr_assert_lt(my_strncmp("HelloThere", "HelloWorld", 6), 0);
}

Test(my_strncmp, difference_within_n)
{
    cr_assert_gt(my_strncmp("abcde", "abZde", 3), 0);
    cr_assert_lt(my_strncmp("abZde", "abcde", 3), 0);
}

Test(my_strncmp, zero_and_negative_n)
{
    cr_assert_eq(my_strncmp("Hello", "World", 0), 0);
    cr_assert_eq(my_strncmp("Hello", "World", -5), 0);
}

Test(my_strncmp, different_lengths)
{
    cr_assert_eq(my_strncmp("Hello", "HelloWorld", 5), 0);
    cr_assert_lt(my_strncmp("Hello", "HelloWorld", 6), 0);
    cr_assert_gt(my_strncmp("HelloWorld", "Hello", 6), 0);
}

Test(my_strncmp, empty_with_non_empty)
{
    cr_assert_lt(my_strncmp("", "abc", 3), 0);
    cr_assert_gt(my_strncmp("abc", "", 3), 0);
}
