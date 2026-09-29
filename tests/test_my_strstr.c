#include <criterion/criterion.h>
#include <stddef.h>
#include "../include/my.h"

Test(my_strstr, substring_in_middle)
{
    char str[] = "Hello, World!";
    char *ret = my_strstr(str, "World");

    cr_assert_not_null(ret);
    cr_assert_eq(ret, &str[7]);
    cr_assert_str_eq(ret, "World!");
}

Test(my_strstr, substring_at_beginning)
{
    char str[] = "Hello, World!";
    char *ret = my_strstr(str, "Hello");

    cr_assert_not_null(ret);
    cr_assert_eq(ret, str);
    cr_assert_str_eq(ret, "Hello, World!");
}

Test(my_strstr, substring_at_end)
{
    char str[] = "Hello, World!";
    char *ret = my_strstr(str, "!");

    cr_assert_not_null(ret);
    cr_assert_eq(ret, &str[12]);
    cr_assert_str_eq(ret, "!");
}

Test(my_strstr, substring_not_found)
{
    char str[] = "Hello, World!";
    char *ret = my_strstr(str, "NotFound");

    cr_assert_null(ret);
}

Test(my_strstr, partial_matches_before_success)
{
    char str[] = "aaaaab";
    char *ret = my_strstr(str, "aab");

    cr_assert_not_null(ret);
    cr_assert_eq(ret, &str[3]);
    cr_assert_str_eq(ret, "aab");
}

Test(my_strstr, empty_needle)
{
    char str[] = "Hello";
    char *ret = my_strstr(str, "");

    cr_assert_not_null(ret);
    cr_assert_eq(ret, str);
}

Test(my_strstr, empty_haystack_non_empty_needle)
{
    char str[] = "";
    char *ret = my_strstr(str, "a");

    cr_assert_null(ret);
}

Test(my_strstr, needle_longer_than_haystack)
{
    char str[] = "short";
    char *ret = my_strstr(str, "longer substring");

    cr_assert_null(ret);
}

Test(my_strstr, single_character_found)
{
    char str[] = "abcdef";
    char *ret = my_strstr(str, "c");

    cr_assert_not_null(ret);
    cr_assert_eq(ret, &str[2]);
    cr_assert_str_eq(ret, "cdef");
}
