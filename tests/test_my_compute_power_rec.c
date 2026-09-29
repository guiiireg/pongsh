#include <criterion/criterion.h>
#include "../include/my.h"

Test(my_compute_power_rec, positive_power)
{
    cr_assert_eq(my_compute_power_rec(2, 3), 8);
    cr_assert_eq(my_compute_power_rec(3, 4), 81);
    cr_assert_eq(my_compute_power_rec(5, 2), 25);
}

Test(my_compute_power_rec, power_zero)
{
    cr_assert_eq(my_compute_power_rec(0, 0), 1);
    cr_assert_eq(my_compute_power_rec(5, 0), 1);
    cr_assert_eq(my_compute_power_rec(-5, 0), 1);
}

Test(my_compute_power_rec, power_one)
{
    cr_assert_eq(my_compute_power_rec(42, 1), 42);
    cr_assert_eq(my_compute_power_rec(-7, 1), -7);
    cr_assert_eq(my_compute_power_rec(0, 1), 0);
}

Test(my_compute_power_rec, negative_power)
{
    cr_assert_eq(my_compute_power_rec(2, -1), 0);
    cr_assert_eq(my_compute_power_rec(5, -3), 0);
    cr_assert_eq(my_compute_power_rec(-4, -2), 0);
}

Test(my_compute_power_rec, negative_base_even_power)
{
    cr_assert_eq(my_compute_power_rec(-2, 4), 16);
    cr_assert_eq(my_compute_power_rec(-3, 2), 9);
}

Test(my_compute_power_rec, negative_base_odd_power)
{
    cr_assert_eq(my_compute_power_rec(-2, 3), -8);
    cr_assert_eq(my_compute_power_rec(-5, 3), -125);
}

Test(my_compute_power_rec, zero_base_positive_power)
{
    cr_assert_eq(my_compute_power_rec(0, 5), 0);
}

Test(my_compute_power_rec, base_one)
{
    cr_assert_eq(my_compute_power_rec(1, 10), 1);
    cr_assert_eq(my_compute_power_rec(1, 0), 1);
    cr_assert_eq(my_compute_power_rec(-1, 2), 1);
    cr_assert_eq(my_compute_power_rec(-1, 3), -1);
}
