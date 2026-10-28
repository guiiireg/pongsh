#include <criterion/criterion.h>
#include "my.h"

Test(my_revstr, odd_length)
{
    char str[6] = "Hello";

    cr_assert_eq(my_revstr(str), 5);
    cr_assert_str_eq(str, "olleH");
}

Test(my_revstr, even_length)
{
    char str[5] = "pong";

    cr_assert_eq(my_revstr(str), 4);
    cr_assert_str_eq(str, "gnop");
}

Test(my_revstr, single_character)
{
    char str[2] = "a";

    cr_assert_eq(my_revstr(str), 1);
    cr_assert_str_eq(str, "a");
}

Test(my_revstr, empty_string)
{
    char str[1] = "";

    cr_assert_eq(my_revstr(str), 0);
    cr_assert_str_eq(str, "");
}

Test(my_revstr, null_input)
{
    cr_assert_eq(my_revstr(NULL), -1);
}
