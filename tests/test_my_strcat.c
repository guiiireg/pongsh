#include <criterion/criterion.h>
#include "../include/my.h"

Test(my_strcat, standard_concatenation)
{
    char dest[50] = "Hello, ";
    const char *src = "World!";
    char *ret = my_strcat(dest, src);

    cr_assert_eq(ret, dest);
    cr_assert_str_eq(dest, "Hello, World!");
}

Test(my_strcat, empty_dest)
{
    char dest[50] = "";
    const char *src = "Hello";
    char *ret = my_strcat(dest, src);

    cr_assert_eq(ret, dest);
    cr_assert_str_eq(dest, "Hello");
}

Test(my_strcat, empty_src)
{
    char dest[50] = "Hello";
    const char *src = "";
    char *ret = my_strcat(dest, src);

    cr_assert_eq(ret, dest);
    cr_assert_str_eq(dest, "Hello");
}

Test(my_strcat, both_empty)
{
    char dest[50] = "";
    const char *src = "";
    char *ret = my_strcat(dest, src);

    cr_assert_eq(ret, dest);
    cr_assert_str_eq(dest, "");
}

Test(my_strcat, single_character_src)
{
    char dest[50] = "Hello";
    const char *src = "!";
    char *ret = my_strcat(dest, src);

    cr_assert_eq(ret, dest);
    cr_assert_str_eq(dest, "Hello!");
}

Test(my_strcat, multiple_concatenations)
{
    char dest[50] = "";

    my_strcat(dest, "foo");
    my_strcat(dest, "bar");
    my_strcat(dest, "baz");
    cr_assert_str_eq(dest, "foobarbaz");
}

Test(my_strcat, special_characters)
{
    char dest[50] = "42";
    const char *src = " \t\n!#";
    char *ret = my_strcat(dest, src);

    cr_assert_eq(ret, dest);
    cr_assert_str_eq(dest, "42 \t\n!#");
}
