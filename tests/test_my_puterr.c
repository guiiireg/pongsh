#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "my.h"

Test(my_puterr, basic, .init = cr_redirect_stderr)
{
    cr_assert_eq(my_puterr("Error"), 5);
    cr_assert_stderr_eq_str("Error");
}

Test(my_puterr, empty_string, .init = cr_redirect_stderr)
{
    cr_assert_eq(my_puterr(""), 0);
    cr_assert_stderr_eq_str("");
}

Test(my_puterr, null_input)
{
    cr_assert_eq(my_puterr(NULL), -1);
}
