#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/my.h"

Test(my_putchar, print_single_char, .init = cr_redirect_stdout)
{
    my_putchar('a');
    cr_assert_stdout_eq_str("a");
}

Test(my_putchar, print_newline, .init = cr_redirect_stdout)
{
    my_putchar('\n');
    cr_assert_stdout_eq_str("\n");
}

Test(my_putchar, print_special_char, .init = cr_redirect_stdout)
{
    my_putchar('#');
    cr_assert_stdout_eq_str("#");
}

Test(my_putchar, print_multiple_chars, .init = cr_redirect_stdout)
{
    my_putchar('H');
    my_putchar('e');
    my_putchar('y');
    cr_assert_stdout_eq_str("Hey");
}
