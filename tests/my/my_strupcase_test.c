#include <criterion/criterion.h>
#include "my/my.h"

Test(my_strupcase, uppercases_mixed_string)
{
    char str[16] = "HeLLo WoRld";

    cr_assert_eq(my_strupcase(str), str);
    cr_assert_str_eq(str, "HELLO WORLD");
}

Test(my_strupcase, keeps_non_letters)
{
    char str[16] = "abc-42_def!";

    my_strupcase(str);
    cr_assert_str_eq(str, "ABC-42_DEF!");
}

Test(my_strupcase, handles_empty_string)
{
    char str[1] = "";

    my_strupcase(str);
    cr_assert_eq(str[0], '\0');
}
