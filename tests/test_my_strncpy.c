#include <criterion/criterion.h>
#include "../include/my.h"

Test(my_strncpy, copy_exact_length)
{
    char dest[10] = {0};
    const char *src = "Hello";
    char *ret = my_strncpy(dest, src, 5);

    cr_assert_eq(ret, dest);
    cr_assert_str_eq(dest, "Hello");
}

Test(my_strncpy, copy_fewer_characters)
{
    char dest[20] = "XXXXXXXXXXXX";
    const char *src = "HelloWorld";
    char *ret = my_strncpy(dest, src, 5);

    dest[5] = '\0';
    cr_assert_eq(ret, dest);
    cr_assert_str_eq(dest, "Hello");
}

Test(my_strncpy, copy_more_characters_than_src)
{
    char dest[10] = "XXXXXXXXX";
    const char *src = "42";
    char *ret = my_strncpy(dest, src, 6);

    cr_assert_eq(ret, dest);
    cr_assert_str_eq(dest, "42");
    cr_assert_eq(dest[2], '\0');
    cr_assert_eq(dest[3], '\0');
    cr_assert_eq(dest[4], '\0');
    cr_assert_eq(dest[5], '\0');
    cr_assert_eq(dest[6], 'X');
}

Test(my_strncpy, copy_zero_characters)
{
    char dest[10] = "Hello";
    const char *src = "World";
    char *ret = my_strncpy(dest, src, 0);

    cr_assert_eq(ret, dest);
    cr_assert_str_eq(dest, "Hello");
}

Test(my_strncpy, copy_empty_string)
{
    char dest[10] = "XXXXXXXXX";
    const char *src = "";
    char *ret = my_strncpy(dest, src, 4);

    cr_assert_eq(ret, dest);
    cr_assert_str_eq(dest, "");
    cr_assert_eq(dest[0], '\0');
    cr_assert_eq(dest[1], '\0');
    cr_assert_eq(dest[2], '\0');
    cr_assert_eq(dest[3], '\0');
    cr_assert_eq(dest[4], 'X');
}
