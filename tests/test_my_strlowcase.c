#include <criterion/criterion.h>
#include "../include/my.h"

Test(my_strlowcase, all_uppercase)
{
    char str[] = "HELLO";
    char *ret = my_strlowcase(str);

    cr_assert_eq(ret, str);
    cr_assert_str_eq(str, "hello");
}

Test(my_strlowcase, already_lowercase)
{
    char str[] = "hello";
    char *ret = my_strlowcase(str);

    cr_assert_eq(ret, str);
    cr_assert_str_eq(str, "hello");
}

Test(my_strlowcase, mixed_case_with_punctuation)
{
    char str[] = "Hello, World! 42";
    char *ret = my_strlowcase(str);

    cr_assert_eq(ret, str);
    cr_assert_str_eq(str, "hello, world! 42");
}

Test(my_strlowcase, empty_string)
{
    char str[] = "";
    char *ret = my_strlowcase(str);

    cr_assert_eq(ret, str);
    cr_assert_str_eq(str, "");
}

Test(my_strlowcase, symbols_and_digits_only)
{
    char str[] = "12345 \t\n!@#$%^&*()";
    char *ret = my_strlowcase(str);

    cr_assert_eq(ret, str);
    cr_assert_str_eq(str, "12345 \t\n!@#$%^&*()");
}

Test(my_strlowcase, ascii_boundaries)
{
    char str[] = "@AZ[";
    char *ret = my_strlowcase(str);

    cr_assert_eq(ret, str);
    cr_assert_str_eq(str, "@az[");
}

Test(my_strlowcase, null_pointer)
{
    char *ret = my_strlowcase(0);

    cr_assert_null(ret);
}
