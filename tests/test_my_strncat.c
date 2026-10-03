#include <criterion/criterion.h>
#include "../include/my.h"

Test(my_strncat, concatenate_partial_src)
{
    char dest[50] = "Hello, ";
    const char *src = "World!";
    char *ret = my_strncat(dest, src, 3);

    cr_assert_eq(ret, dest);
    cr_assert_str_eq(dest, "Hello, Wor");
}

Test(my_strncat, concatenate_exact_length)
{
    char dest[50] = "Hello, ";
    const char *src = "World!";
    char *ret = my_strncat(dest, src, 6);

    cr_assert_eq(ret, dest);
    cr_assert_str_eq(dest, "Hello, World!");
}

Test(my_strncat, concatenate_more_than_length)
{
    char dest[50] = "Hello, ";
    const char *src = "World!";
    char *ret = my_strncat(dest, src, 50);

    cr_assert_eq(ret, dest);
    cr_assert_str_eq(dest, "Hello, World!");
}

Test(my_strncat, zero_and_negative_nb)
{
    char dest1[50] = "Hello";
    char dest2[50] = "Hello";
    const char *src = "World";

    cr_assert_eq(my_strncat(dest1, src, 0), dest1);
    cr_assert_str_eq(dest1, "Hello");
    cr_assert_eq(my_strncat(dest2, src, -3), dest2);
    cr_assert_str_eq(dest2, "Hello");
}

Test(my_strncat, empty_dest)
{
    char dest[50] = "";
    const char *src = "HelloWorld";
    char *ret = my_strncat(dest, src, 5);

    cr_assert_eq(ret, dest);
    cr_assert_str_eq(dest, "Hello");
}

Test(my_strncat, empty_src)
{
    char dest[50] = "Hello";
    const char *src = "";
    char *ret = my_strncat(dest, src, 5);

    cr_assert_eq(ret, dest);
    cr_assert_str_eq(dest, "Hello");
}

Test(my_strncat, chained_calls)
{
    char dest[50] = "";

    my_strncat(dest, "abcdef", 2);
    my_strncat(dest, "123456", 3);
    cr_assert_str_eq(dest, "ab123");
}
