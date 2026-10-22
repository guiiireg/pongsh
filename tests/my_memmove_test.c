#include <criterion/criterion.h>
#include <string.h>
#include "../include/my.h"

Test(my_memmove, copies_without_overlap)
{
    char src[16] = "0123456789";
    char dest[16] = "aaaaaaaaaa";

    cr_assert_eq(my_memmove(dest, src, 11), dest);
    cr_assert_str_eq(dest, "0123456789");
}

Test(my_memmove, handles_forward_overlap)
{
    char buf[16] = "0123456789";

    my_memmove(buf + 2, buf, 8);
    cr_assert_str_eq(buf, "010123456789");
}

Test(my_memmove, handles_backward_overlap)
{
    char buf[16] = "0123456789";

    my_memmove(buf, buf + 2, 8);
    cr_assert_str_eq(buf, "2345678989");
}

Test(my_memmove, handles_identical_buffers)
{
    char buf[8] = "abcdefg";

    my_memmove(buf, buf, 8);
    cr_assert_str_eq(buf, "abcdefg");
}

Test(my_memmove, copies_zero_bytes)
{
    char buf[8] = "abcdefg";

    my_memmove(buf, buf + 1, 0);
    cr_assert_str_eq(buf, "abcdefg");
}
