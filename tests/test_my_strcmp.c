#include <criterion/criterion.h>
#include "../include/my.h"

Test(my_strcmp, identical_strings)
{
    cr_assert_eq(my_strcmp("Hello", "Hello"), 0);
    cr_assert_eq(my_strcmp("", ""), 0);
    cr_assert_eq(my_strcmp("42", "42"), 0);
}

Test(my_strcmp, first_string_greater)
{
    cr_assert_gt(my_strcmp("b", "a"), 0);
    cr_assert_gt(my_strcmp("HelloB", "HelloA"), 0);
    cr_assert_gt(my_strcmp("abc", "ABC"), 0);
}

Test(my_strcmp, first_string_less)
{
    cr_assert_lt(my_strcmp("a", "b"), 0);
    cr_assert_lt(my_strcmp("HelloA", "HelloB"), 0);
    cr_assert_lt(my_strcmp("ABC", "abc"), 0);
}

Test(my_strcmp, different_lengths)
{
    cr_assert_lt(my_strcmp("Hello", "HelloWorld"), 0);
    cr_assert_gt(my_strcmp("HelloWorld", "Hello"), 0);
}

Test(my_strcmp, empty_with_non_empty)
{
    cr_assert_lt(my_strcmp("", "a"), 0);
    cr_assert_gt(my_strcmp("a", ""), 0);
}
