#include <criterion/criterion.h>
#include <limits.h>
#include "../include/my.h"

Test(my_is_prime, small_primes)
{
    cr_assert_eq(my_is_prime(2), 1);
    cr_assert_eq(my_is_prime(3), 1);
    cr_assert_eq(my_is_prime(5), 1);
    cr_assert_eq(my_is_prime(7), 1);
    cr_assert_eq(my_is_prime(11), 1);
    cr_assert_eq(my_is_prime(13), 1);
    cr_assert_eq(my_is_prime(97), 1);
}

Test(my_is_prime, larger_primes)
{
    cr_assert_eq(my_is_prime(101), 1);
    cr_assert_eq(my_is_prime(1009), 1);
    cr_assert_eq(my_is_prime(INT_MAX), 1);
}

Test(my_is_prime, non_primes)
{
    cr_assert_eq(my_is_prime(0), 0);
    cr_assert_eq(my_is_prime(1), 0);
    cr_assert_eq(my_is_prime(4), 0);
    cr_assert_eq(my_is_prime(6), 0);
    cr_assert_eq(my_is_prime(8), 0);
    cr_assert_eq(my_is_prime(9), 0);
    cr_assert_eq(my_is_prime(15), 0);
    cr_assert_eq(my_is_prime(21), 0);
    cr_assert_eq(my_is_prime(25), 0);
    cr_assert_eq(my_is_prime(27), 0);
    cr_assert_eq(my_is_prime(49), 0);
    cr_assert_eq(my_is_prime(121), 0);
}

Test(my_is_prime, negative_numbers)
{
    cr_assert_eq(my_is_prime(-1), 0);
    cr_assert_eq(my_is_prime(-2), 0);
    cr_assert_eq(my_is_prime(-7), 0);
    cr_assert_eq(my_is_prime(-42), 0);
    cr_assert_eq(my_is_prime(INT_MIN), 0);
}
