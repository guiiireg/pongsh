#include <criterion/criterion.h>
#include "../include/my.h"

Test(my_putstr, test_putstr_hello) {
    cr_redirect_stdout();
    int result = my_putstr("hello");
    cr_assert_stdout_eq_str("hello");
    cr_assert_eq(result, 5);
}

Test(my_putstr, test_putstr_empty) {
    cr_redirect_stdout();
    int result = my_putstr("");
    cr_assert_stdout_eq_str("");
    cr_assert_eq(result, 0);
}

Test(my_putstr, test_putstr_with_newline) {
    cr_redirect_stdout();
    int result = my_putstr("line1\nline2");
    cr_assert_stdout_eq_str("line1\nline2");
    cr_assert_eq(result, 11);
}

Test(my_putstr, test_putstr_special_chars) {
    cr_redirect_stdout();
    int result = my_putstr("!@#$%^&*()");
    cr_assert_stdout_eq_str("!@#$%^&*()");
    cr_assert_eq(result, 10);
}

Test(my_putstr, test_putstr_null) {
    cr_redirect_stdout();
    int result = my_putstr(NULL);
    cr_assert_stdout_eq_str("");
    cr_assert_eq(result, 0);
}