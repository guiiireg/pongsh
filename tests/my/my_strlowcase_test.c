#include <criterion/criterion.h>
#include "my/my.h"

Test(my_strlowcase, lowercases_mixed_string)
{
    char str[16] = "HeLLo WoRld";

    cr_assert_eq(my_strlowcase(str), str);
    cr_assert_str_eq(str, "hello world");
}

Test(my_strlowcase, keeps_non_letters)
{
    char str[16] = "ABC-42_DEF!";

    my_strlowcase(str);
    cr_assert_str_eq(str, "abc-42_def!");
}

Test(my_strlowcase, handles_empty_string)
{
    char str[1] = "";

    my_strlowcase(str);
    cr_assert_eq(str[0], '\0');
}
