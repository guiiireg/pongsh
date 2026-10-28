#include <criterion/criterion.h>
#include "my.h"

Test(my_strlen, basic)
{
    cr_assert_eq(my_strlen("Hello"), 5);
    cr_assert_eq(my_strlen("pongsh"), 6);
}

Test(my_strlen, empty_string)
{
    cr_assert_eq(my_strlen(""), 0);
}

Test(my_strlen, single_character)
{
    cr_assert_eq(my_strlen("a"), 1);
}

Test(my_strlen, null_input)
{
    cr_assert_eq(my_strlen(NULL), -1);
}
