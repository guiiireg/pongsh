#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "my.h"

Test(my_putstr, basic, .init = cr_redirect_stdout)
{
    cr_assert_eq(my_putstr("Hello"), 5);
    cr_assert_stdout_eq_str("Hello");
}

Test(my_putstr, empty_string, .init = cr_redirect_stdout)
{
    cr_assert_eq(my_putstr(""), 0);
    cr_assert_stdout_eq_str("");
}

Test(my_putstr, null_input)
{
    cr_assert_eq(my_putstr(NULL), -1);
}
