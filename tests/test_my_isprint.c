#include <criterion/criterion.h>
#include "my.h"

Test(my_isprint, printable_characters)
{
    cr_assert_eq(my_isprint(' '), 1);
    cr_assert_eq(my_isprint('~'), 1);
    cr_assert_eq(my_isprint('a'), 1);
}

Test(my_isprint, non_printable)
{
    cr_assert_eq(my_isprint(31), 0);
    cr_assert_eq(my_isprint(127), 0);
    cr_assert_eq(my_isprint(0), 0);
}
