#include <criterion/criterion.h>
#include <limits.h>
#include "../include/my.h"

Test(my_getnbr, positive_number)
{
    cr_assert_eq(my_getnbr("42"), 42);
}

Test(my_getnbr, negative_number)
{
    cr_assert_eq(my_getnbr("-42"), -42);
}

Test(my_getnbr, zero_number)
{
    cr_assert_eq(my_getnbr("0"), 0);
    cr_assert_eq(my_getnbr("-0"), 0);
    cr_assert_eq(my_getnbr("+0"), 0);
}

Test(my_getnbr, multiple_signs)
{
    cr_assert_eq(my_getnbr("--42"), 42);
    cr_assert_eq(my_getnbr("---42"), -42);
    cr_assert_eq(my_getnbr("+---+--++42abc58"), -42);
}

Test(my_getnbr, trailing_non_digits)
{
    cr_assert_eq(my_getnbr("42hello"), 42);
    cr_assert_eq(my_getnbr("-1337world"), -1337);
}

Test(my_getnbr, no_digits_or_invalid)
{
    cr_assert_eq(my_getnbr(""), 0);
    cr_assert_eq(my_getnbr(NULL), 0);
    cr_assert_eq(my_getnbr("abc"), 0);
    cr_assert_eq(my_getnbr("+-+-+"), 0);
}

Test(my_getnbr, leading_zeros)
{
    cr_assert_eq(my_getnbr("000042"), 42);
    cr_assert_eq(my_getnbr("-000042"), -42);
}

Test(my_getnbr, max_int)
{
    cr_assert_eq(my_getnbr("2147483647"), INT_MAX);
}

Test(my_getnbr, min_int)
{
    cr_assert_eq(my_getnbr("-2147483648"), INT_MIN);
}

Test(my_getnbr, overflow_positive)
{
    cr_assert_eq(my_getnbr("2147483648"), 0);
    cr_assert_eq(my_getnbr("99999999999999999999"), 0);
}

Test(my_getnbr, overflow_negative)
{
    cr_assert_eq(my_getnbr("-2147483649"), 0);
    cr_assert_eq(my_getnbr("-99999999999999999999"), 0);
}
