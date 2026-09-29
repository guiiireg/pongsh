#include <criterion/criterion.h>
#include "../include/my.h"

Test(my_strupcase, all_lowercase)
{
    char str[] = "hello";
    char *ret = my_strupcase(str);

    cr_assert_eq(ret, str);
    cr_assert_str_eq(str, "HELLO");
}

Test(my_strupcase, already_uppercase)
{
    char str[] = "HELLO";
    char *ret = my_strupcase(str);

    cr_assert_eq(ret, str);
    cr_assert_str_eq(str, "HELLO");
}

Test(my_strupcase, mixed_case_with_punctuation)
{
    char str[] = "Hello, World! 42";
    char *ret = my_strupcase(str);

    cr_assert_eq(ret, str);
    cr_assert_str_eq(str, "HELLO, WORLD! 42");
}

Test(my_strupcase, empty_string)
{
    char str[] = "";
    char *ret = my_strupcase(str);

    cr_assert_eq(ret, str);
    cr_assert_str_eq(str, "");
}

Test(my_strupcase, symbols_and_digits_only)
{
    char str[] = "12345 \t\n!@#$%^&*()";
    char *ret = my_strupcase(str);

    cr_assert_eq(ret, str);
    cr_assert_str_eq(str, "12345 \t\n!@#$%^&*()");
}

Test(my_strupcase, ascii_boundaries)
{
    char str[] = "`az{";
    char *ret = my_strupcase(str);

    cr_assert_eq(ret, str);
    cr_assert_str_eq(str, "`AZ{");
}
