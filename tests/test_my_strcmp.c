#include <criterion/criterion.h>
#include "my.h"

Test(my_strcmp, equal_strings)
{
    cr_assert_eq(my_strcmp("Hello", "Hello"), 0);
    cr_assert_eq(my_strcmp("", ""), 0);
}

Test(my_strcmp, lower_string)
{
    cr_assert_lt(my_strcmp("abc", "abd"), 0);
    cr_assert_lt(my_strcmp("ab", "abc"), 0);
}

Test(my_strcmp, greater_string)
{
    cr_assert_gt(my_strcmp("abd", "abc"), 0);
    cr_assert_gt(my_strcmp("abc", "ab"), 0);
}

Test(my_strcmp, sign_is_symmetric)
{
    cr_assert_lt(my_strcmp("a", "b"), 0);
    cr_assert_gt(my_strcmp("b", "a"), 0);
}

Test(my_strcmp, null_arguments)
{
    cr_assert_eq(my_strcmp(NULL, "Hello"), -1);
    cr_assert_eq(my_strcmp("Hello", NULL), -1);
}
