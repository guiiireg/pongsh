#include <criterion/criterion.h>
#include "my.h"

Test(my_isalpha, uppercase_letter)
{
    cr_assert_eq(my_isalpha('A'), 1);
    cr_assert_eq(my_isalpha('Z'), 1);
}

Test(my_isalpha, lowercase_letter)
{
    cr_assert_eq(my_isalpha('a'), 1);
    cr_assert_eq(my_isalpha('z'), 1);
}

Test(my_isalpha, digit)
{
    cr_assert_eq(my_isalpha('0'), 0);
}

Test(my_isalpha, non_letter)
{
    cr_assert_eq(my_isalpha('!'), 0);
    cr_assert_eq(my_isalpha(' '), 0);
}
