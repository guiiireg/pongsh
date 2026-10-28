#include <criterion/criterion.h>
#include "my.h"

Test(my_memset, fill_bytes)
{
    char buf[6] = "XXXXX";

    cr_assert_eq(my_memset(buf, 'A', 3), buf);
    cr_assert_eq(buf[0], 'A');
    cr_assert_eq(buf[2], 'A');
    cr_assert_eq(buf[3], 'X');
}

Test(my_memset, zero_length)
{
    char buf[6] = "Hello";

    cr_assert_eq(my_memset(buf, 'A', 0), buf);
    cr_assert_str_eq(buf, "Hello");
}

Test(my_memset, value_truncated_to_unsigned_char)
{
    char buf[2] = "X";

    my_memset(buf, 0x141, 1);
    cr_assert_eq(buf[0], 'A');
}

Test(my_memset, invalid_arguments)
{
    char buf[6] = "XXXXX";

    cr_assert_null(my_memset(NULL, 'A', 3));
    cr_assert_null(my_memset(buf, 'A', -1));
}
