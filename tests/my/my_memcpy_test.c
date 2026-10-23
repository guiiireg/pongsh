#include <criterion/criterion.h>
#include <string.h>
#include "my/my.h"

Test(my_memcpy, copies_bytes)
{
    char src[8] = "hello";
    char dest[16] = "xxxxxxxx";

    cr_assert_eq(my_memcpy(dest, src, 6), dest);
    cr_assert_str_eq(dest, "hello");
}

Test(my_memcpy, copies_zero_bytes)
{
    char src[8] = "hello";
    char dest[16] = "xxxxxxxx";

    my_memcpy(dest, src, 0);
    cr_assert_str_eq(dest, "xxxxxxxx");
}

Test(my_memcpy, copies_partial_buffer)
{
    char src[8] = "hello";
    char dest[16] = "xxxxxxxx";

    my_memcpy(dest, src, 3);
    cr_assert_eq(dest[0], 'h');
    cr_assert_eq(dest[1], 'e');
    cr_assert_eq(dest[2], 'l');
    cr_assert_eq(dest[3], 'x');
}

Test(my_memcpy, copies_binary_data)
{
    char src[4] = {0x01, 0x02, 0x03, 0x04};
    char dest[4] = {0, 0, 0, 0};

    my_memcpy(dest, src, 4);
    cr_assert_eq(my_memcmp(dest, src, 4), 0);
}
