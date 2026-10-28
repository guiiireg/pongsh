#include <criterion/criterion.h>
#include "my.h"

Test(my_toupper, lowercase_letters)
{
    cr_assert_eq(my_toupper('a'), 'A');
    cr_assert_eq(my_toupper('z'), 'Z');
}

Test(my_toupper, unchanged)
{
    cr_assert_eq(my_toupper('A'), 'A');
    cr_assert_eq(my_toupper('!'), '!');
    cr_assert_eq(my_toupper('0'), '0');
}
