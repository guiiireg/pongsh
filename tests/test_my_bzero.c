#include <criterion/criterion.h>
#include "my.h"

Test(my_bzero, zeroes_bytes)
{
    char buf[6] = "Hello";

    cr_assert_eq(my_bzero(buf, 2), 0);
    cr_assert_eq(buf[0], '\0');
    cr_assert_eq(buf[1], '\0');
    cr_assert_eq(buf[2], 'l');
}

Test(my_bzero, full_buffer)
{
    char buf[6] = "Hello";

    cr_assert_eq(my_bzero(buf, 5), 0);
    cr_assert_eq(buf[4], '\0');
}

Test(my_bzero, invalid_arguments)
{
    char buf[6] = "Hello";

    cr_assert_eq(my_bzero(NULL, 2), -1);
    cr_assert_eq(my_bzero(buf, -1), -1);
}
