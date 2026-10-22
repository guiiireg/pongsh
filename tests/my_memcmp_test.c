#include <criterion/criterion.h>
#include "../include/my.h"

Test(my_memcmp, equal_buffers_return_zero)
{
    cr_assert_eq(my_memcmp("abcdef", "abcdef", 6), 0);
}

Test(my_memcmp, difference_returns_correct_sign)
{
    cr_assert_lt(my_memcmp("abcxyz", "abcdef", 6), 0);
    cr_assert_gt(my_memcmp("abcdef", "abcxyz", 6), 0);
}

Test(my_memcmp, difference_after_n_is_ignored)
{
    cr_assert_eq(my_memcmp("abcZZZ", "abcXXX", 3), 0);
}

Test(my_memcmp, zero_size_returns_zero)
{
    cr_assert_eq(my_memcmp("abc", "xyz", 0), 0);
}

Test(my_memcmp, stops_at_first_difference)
{
    cr_assert_lt(my_memcmp("\0abc", "\0xyz", 4), 0);
}
