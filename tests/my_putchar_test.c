#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/my.h"

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
}

Test(my_putchar, prints_one_char, .init = redirect_all_stdout)
{
    my_putchar('a');
    cr_assert_stdout_eq_str("a");
}

Test(my_putchar, prints_digit_char, .init = redirect_all_stdout)
{
    my_putchar('0');
    cr_assert_stdout_eq_str("0");
}

Test(my_putchar, prints_newline, .init = redirect_all_stdout)
{
    my_putchar('\n');
    cr_assert_stdout_eq_str("\n");
}
