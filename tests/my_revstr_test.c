#include <criterion/criterion.h>
#include "../include/my.h"

Test(my_revstr, reverses_odd_length_string)
{
    char str[6] = "hello";

    cr_assert_eq(my_revstr(str), str);
    cr_assert_str_eq(str, "olleh");
}

Test(my_revstr, reverses_even_length_string)
{
    char str[5] = "abcd";

    my_revstr(str);
    cr_assert_str_eq(str, "dcba");
}

Test(my_revstr, reverses_single_char)
{
    char str[2] = "a";

    my_revstr(str);
    cr_assert_str_eq(str, "a");
}

Test(my_revstr, reverses_empty_string)
{
    char str[1] = "";

    my_revstr(str);
    cr_assert_eq(str[0], '\0');
}
