#include <criterion/criterion.h>
#include "../include/my.h"

Test(my_revstr, standard_odd_length)
{
    char str[] = "Hello";
    char *ret = my_revstr(str);

    cr_assert_eq(ret, str);
    cr_assert_str_eq(str, "olleH");
}

Test(my_revstr, standard_even_length)
{
    char str[] = "abcdef";
    char *ret = my_revstr(str);

    cr_assert_eq(ret, str);
    cr_assert_str_eq(str, "fedcba");
}

Test(my_revstr, two_characters)
{
    char str[] = "42";
    char *ret = my_revstr(str);

    cr_assert_eq(ret, str);
    cr_assert_str_eq(str, "24");
}

Test(my_revstr, single_character)
{
    char str[] = "x";
    char *ret = my_revstr(str);

    cr_assert_eq(ret, str);
    cr_assert_str_eq(str, "x");
}

Test(my_revstr, empty_string)
{
    char str[] = "";
    char *ret = my_revstr(str);

    cr_assert_eq(ret, str);
    cr_assert_str_eq(str, "");
}

Test(my_revstr, palindrome)
{
    char str[] = "racecar";
    char *ret = my_revstr(str);

    cr_assert_eq(ret, str);
    cr_assert_str_eq(str, "racecar");
}

Test(my_revstr, with_spaces_and_punctuation)
{
    char str[] = "Hello, World!";
    char *ret = my_revstr(str);

    cr_assert_eq(ret, str);
    cr_assert_str_eq(str, "!dlroW ,olleH");
}
