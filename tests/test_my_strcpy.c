#include <criterion/criterion.h>
#include "../include/my.h"

Test(my_strcpy, standard_string)
{
    char dest[50];
    const char *src = "Hello, World!";
    char *ret = my_strcpy(dest, src);

    cr_assert_eq(ret, dest);
    cr_assert_str_eq(dest, src);
}

Test(my_strcpy, empty_string)
{
    char dest[10];
    const char *src = "";
    char *ret = my_strcpy(dest, src);

    cr_assert_eq(ret, dest);
    cr_assert_str_eq(dest, "");
}

Test(my_strcpy, single_character)
{
    char dest[10];
    const char *src = "a";
    char *ret = my_strcpy(dest, src);

    cr_assert_eq(ret, dest);
    cr_assert_str_eq(dest, "a");
}

Test(my_strcpy, special_characters)
{
    char dest[50];
    const char *src = "Hello\t\n123!@#";
    char *ret = my_strcpy(dest, src);

    cr_assert_eq(ret, dest);
    cr_assert_str_eq(dest, src);
}

Test(my_strcpy, overwrite_existing_buffer)
{
    char dest[20] = "ExistingContent";
    const char *src = "New";
    char *ret = my_strcpy(dest, src);

    cr_assert_eq(ret, dest);
    cr_assert_str_eq(dest, "New");
}

Test(my_strcpy, long_string)
{
    char dest[100];
    const char *src = "The quick brown fox jumps over the lazy dog";
    char *ret = my_strcpy(dest, src);

    cr_assert_eq(ret, dest);
    cr_assert_str_eq(dest, src);
}
