#include <criterion/criterion.h>
#include "../include/my.h"

Test(my_swap, swap_positive_integers)
{
    int a = 12;
    int b = 42;

    my_swap(&a, &b);
    cr_assert_eq(a, 42);
    cr_assert_eq(b, 12);
}

Test(my_swap, swap_negative_integers)
{
    int a = -5;
    int b = -42;

    my_swap(&a, &b);
    cr_assert_eq(a, -42);
    cr_assert_eq(b, -5);
}

Test(my_swap, swap_same_values)
{
    int a = 10;
    int b = 10;

    my_swap(&a, &b);
    cr_assert_eq(a, 10);
    cr_assert_eq(b, 10);
}

Test(my_swap, swap_with_zero)
{
    int a = 0;
    int b = 25;

    my_swap(&a, &b);
    cr_assert_eq(a, 25);
    cr_assert_eq(b, 0);
}
