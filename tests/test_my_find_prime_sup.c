#include <criterion/criterion.h>
#include <limits.h>
#include "../include/my.h"

Test(my_find_prime_sup, negative_and_low_values)
{
    cr_assert_eq(my_find_prime_sup(-10), 2);
    cr_assert_eq(my_find_prime_sup(-1), 2);
    cr_assert_eq(my_find_prime_sup(0), 2);
    cr_assert_eq(my_find_prime_sup(1), 2);
    cr_assert_eq(my_find_prime_sup(2), 2);
}

Test(my_find_prime_sup, already_prime)
{
    cr_assert_eq(my_find_prime_sup(3), 3);
    cr_assert_eq(my_find_prime_sup(5), 5);
    cr_assert_eq(my_find_prime_sup(7), 7);
    cr_assert_eq(my_find_prime_sup(11), 11);
    cr_assert_eq(my_find_prime_sup(13), 13);
    cr_assert_eq(my_find_prime_sup(97), 97);
}

Test(my_find_prime_sup, composite_numbers)
{
    cr_assert_eq(my_find_prime_sup(4), 5);
    cr_assert_eq(my_find_prime_sup(8), 11);
    cr_assert_eq(my_find_prime_sup(14), 17);
    cr_assert_eq(my_find_prime_sup(24), 29);
    cr_assert_eq(my_find_prime_sup(90), 97);
}

Test(my_find_prime_sup, max_int_prime)
{
    cr_assert_eq(my_find_prime_sup(INT_MAX), INT_MAX);
}
