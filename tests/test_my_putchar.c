#include <criterion/criterion.h>
#include "../include/my.h"

Test(my_putchar, test_putchar_a) {
    cr_redirect_stdout();
    my_putchar('a');
    cr_assert_stdout_eq_str("a");
}

Test(my_putchar, test_putchar_newline) {
    cr_redirect_stdout();
    my_putchar('\n');
    cr_assert_stdout_eq_str("\n");
}

Test(my_putchar, test_putchar_digit) {
    cr_redirect_stdout();
    my_putchar('5');
    cr_assert_stdout_eq_str("5");
}

Test(my_putchar, test_putchar_special) {
    cr_redirect_stdout();
    my_putchar('!');
    cr_assert_stdout_eq_str("!");
}
