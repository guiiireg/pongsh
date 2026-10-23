#include <criterion/criterion.h>
#include "../include/my.h"

Test(my_memset, fills_buffer_with_byte)
{
    char buf[16] = "AAAAAAAA";

    cr_assert_eq(my_memset(buf, 'x', 4), buf);
    cr_assert_str_eq(buf, "xxxxAAAA");
}

Test(my_memset, fills_entire_buffer)
{
    char buf[8] = "aaaa";

    my_memset(buf, 'z', 4);
    cr_assert_str_eq(buf, "zzzz");
}

Test(my_memset, fills_zero_bytes)
{
    char buf[8] = "aaaa";

    my_memset(buf, 'z', 0);
    cr_assert_str_eq(buf, "aaaa");
}

Test(my_memset, fills_with_zero_value)
{
    char buf[8] = "aaaa";

    my_memset(buf, 0, 2);
    cr_assert_eq(buf[0], '\0');
    cr_assert_eq(buf[1], '\0');
    cr_assert_eq(buf[2], 'a');
}
