#include <criterion/criterion.h>
#include "my.h"

Test(my_strncmp, equal_segments)
{
    cr_assert_eq(my_strncmp("Hello", "Hello", 5), 0);
    cr_assert_eq(my_strncmp("Hello", "Hello", 10), 0);
}

Test(my_strncmp, equal_prefix_only)
{
    cr_assert_eq(my_strncmp("Hello", "Help", 3), 0);
    cr_assert_lt(my_strncmp("Hello", "Help", 4), 0);
}

Test(my_strncmp, signed_difference)
{
    cr_assert_lt(my_strncmp("abc", "ade", 2), 0);
    cr_assert_gt(my_strncmp("ade", "abc", 2), 0);
}

Test(my_strncmp, zero_length)
{
    cr_assert_eq(my_strncmp("Hello", "World", 0), 0);
}

Test(my_strncmp, invalid_arguments)
{
    cr_assert_eq(my_strncmp(NULL, "Hello", 2), -1);
    cr_assert_eq(my_strncmp("Hello", NULL, 2), -1);
    cr_assert_eq(my_strncmp("Hello", "World", -1), -1);
}
