#include <criterion/criterion.h>
#include "../include/my.h"

Test(my_put_nbr, test_put_nbr_zero) {
    cr_redirect_stdout();
    int result = my_put_nbr(0);
    cr_assert_stdout_eq_str("0");
    cr_assert_eq(result, 1);
}

Test(my_put_nbr, test_put_nbr_positive) {
    cr_redirect_stdout();
    int result = my_put_nbr(42);
    cr_assert_stdout_eq_str("42");
    cr_assert_eq(result, 2);
}

Test(my_put_nbr, test_put_nbr_negative) {
    cr_redirect_stdout();
    int result = my_put_nbr(-42);
    cr_assert_stdout_eq_str("-42");
    cr_assert_eq(result, 3);
}

Test(my_put_nbr, test_put_nbr_max_int) {
    cr_redirect_stdout();
    int result = my_put_nbr(2147483647);
    cr_assert_stdout_eq_str("2147483647");
    cr_assert_eq(result, 10);
}

Test(my_put_nbr, test_put_nbr_min_int) {
    cr_redirect_stdout();
    int result = my_put_nbr(-2147483648);
    cr_assert_stdout_eq_str("-2147483648");
    cr_assert_eq(result, 11);
}