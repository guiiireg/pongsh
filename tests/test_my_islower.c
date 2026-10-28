#include <criterion/criterion.h>
#include "my.h"

Test(my_islower, lowercase_letters)
{
    cr_assert_eq(my_islower('a'), 1);
    cr_assert_eq(my_islower('z'), 1);
}

Test(my_islower, non_lowercase)
{
    cr_assert_eq(my_islower('A'), 0);
    cr_assert_eq(my_islower('{'), 0);
    cr_assert_eq(my_islower('`'), 0);
}
