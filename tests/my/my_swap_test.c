#include <criterion/criterion.h>
#include "my/my.h"

Test(my_swap, swaps_two_values)
{
    int a = 1;
    int b = 2;

    my_swap(&a, &b);
    cr_assert_eq(a, 2);
    cr_assert_eq(b, 1);
}

Test(my_swap, swaps_equal_values)
{
    int a = 7;
    int b = 7;

    my_swap(&a, &b);
    cr_assert_eq(a, 7);
    cr_assert_eq(b, 7);
}

Test(my_swap, swaps_negative_values)
{
    int a = -5;
    int b = 5;

    my_swap(&a, &b);
    cr_assert_eq(a, 5);
    cr_assert_eq(b, -5);
}
