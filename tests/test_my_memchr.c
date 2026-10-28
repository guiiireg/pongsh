#include <criterion/criterion.h>
#include "my.h"

Test(my_memchr, found)
{
    char buf[6] = "Hello";

    cr_assert_eq(my_memchr(buf, 'l', 5), buf + 2);
}

Test(my_memchr, not_found)
{
    cr_assert_null(my_memchr("Hello", 'z', 5));
}

Test(my_memchr, outside_searched_range)
{
    char buf[6] = "Hello";

    cr_assert_null(my_memchr(buf, 'o', 3));
    cr_assert_eq(my_memchr(buf, 'o', 5), buf + 4);
}

Test(my_memchr, finds_null_byte)
{
    char buf[6] = "Hi";

    cr_assert_eq(my_memchr(buf, '\0', 3), buf + 2);
}

Test(my_memchr, invalid_arguments)
{
    cr_assert_null(my_memchr(NULL, 'a', 3));
    cr_assert_null(my_memchr("Hello", 'a', -1));
}
