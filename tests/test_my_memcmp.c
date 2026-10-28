#include <criterion/criterion.h>
#include "my.h"

Test(my_memcmp, equal_areas)
{
    cr_assert_eq(my_memcmp("Hello", "Hello", 5), 0);
}

Test(my_memcmp, signed_difference)
{
    cr_assert_lt(my_memcmp("abc", "abd", 3), 0);
    cr_assert_gt(my_memcmp("abd", "abc", 3), 0);
}

Test(my_memcmp, stops_at_length)
{
    cr_assert_eq(my_memcmp("abc", "abd", 2), 0);
}

Test(my_memcmp, compares_null_bytes)
{
    cr_assert_eq(my_memcmp("ab\0d", "ab\0d", 4), 0);
    cr_assert_lt(my_memcmp("ab\0c", "ab\0d", 4), 0);
}

Test(my_memcmp, zero_length)
{
    cr_assert_eq(my_memcmp("Hello", "World", 0), 0);
}

Test(my_memcmp, invalid_arguments)
{
    cr_assert_eq(my_memcmp(NULL, "Hello", 3), -1);
    cr_assert_eq(my_memcmp("Hello", NULL, 3), -1);
    cr_assert_eq(my_memcmp("Hello", "World", -1), -1);
}
