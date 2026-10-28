#include <criterion/criterion.h>
#include "my.h"

Test(my_tolower, uppercase_letters)
{
    cr_assert_eq(my_tolower('A'), 'a');
    cr_assert_eq(my_tolower('Z'), 'z');
}

Test(my_tolower, unchanged)
{
    cr_assert_eq(my_tolower('a'), 'a');
    cr_assert_eq(my_tolower('!'), '!');
    cr_assert_eq(my_tolower('0'), '0');
}
