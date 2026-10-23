#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "my/my.h"

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
}

Test(my_putstr, prints_string_and_returns_len, .init = redirect_all_stdout)
{
    cr_assert_eq(my_putstr("hello"), 5);
    cr_assert_stdout_eq_str("hello");
}

Test(my_putstr, prints_empty_string, .init = redirect_all_stdout)
{
    cr_assert_eq(my_putstr(""), 0);
    cr_assert_stdout_eq_str("");
}

Test(my_putstr, prints_long_string, .init = redirect_all_stdout)
{
    cr_assert_eq(my_putstr("a longer string here"), 20);
    cr_assert_stdout_eq_str("a longer string here");
}
