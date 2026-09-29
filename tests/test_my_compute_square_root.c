#include <criterion/criterion.h>
#include <limits.h>
#include "../include/my.h"

Test(my_compute_square_root, perfect_squares)
{
    cr_assert_eq(my_compute_square_root(1), 1);
    cr_assert_eq(my_compute_square_root(4), 2);
    cr_assert_eq(my_compute_square_root(9), 3);
    cr_assert_eq(my_compute_square_root(16), 4);
    cr_assert_eq(my_compute_square_root(25), 5);
    cr_assert_eq(my_compute_square_root(100), 10);
    cr_assert_eq(my_compute_square_root(144), 12);
}

Test(my_compute_square_root, large_perfect_square)
{
    cr_assert_eq(my_compute_square_root(2147395600), 46340);
}

Test(my_compute_square_root, non_perfect_squares)
{
    cr_assert_eq(my_compute_square_root(2), 0);
    cr_assert_eq(my_compute_square_root(3), 0);
    cr_assert_eq(my_compute_square_root(5), 0);
    cr_assert_eq(my_compute_square_root(8), 0);
    cr_assert_eq(my_compute_square_root(10), 0);
    cr_assert_eq(my_compute_square_root(42), 0);
}

Test(my_compute_square_root, zero_and_negative)
{
    cr_assert_eq(my_compute_square_root(0), 0);
    cr_assert_eq(my_compute_square_root(-1), 0);
    cr_assert_eq(my_compute_square_root(-4), 0);
    cr_assert_eq(my_compute_square_root(-42), 0);
    cr_assert_eq(my_compute_square_root(INT_MIN), 0);
}

Test(my_compute_square_root, max_int)
{
    cr_assert_eq(my_compute_square_root(INT_MAX), 0);
}
