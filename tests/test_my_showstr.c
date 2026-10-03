#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/my.h"

Test(my_showstr, printable_string, .init = cr_redirect_stdout)
{
    int ret = my_showstr("Hello World!");

    cr_assert_eq(ret, 0);
    cr_assert_stdout_eq_str("Hello World!");
}

Test(my_showstr, empty_string, .init = cr_redirect_stdout)
{
    int ret = my_showstr("");

    cr_assert_eq(ret, 0);
    cr_assert_stdout_eq_str("");
}

Test(my_showstr, null_pointer, .init = cr_redirect_stdout)
{
    int ret = my_showstr(0);

    cr_assert_eq(ret, 0);
    cr_assert_stdout_eq_str("");
}

Test(my_showstr, with_non_printable_characters, .init = cr_redirect_stdout)
{
    int ret = my_showstr("Hello\nWorld!\t\x07");

    cr_assert_eq(ret, 0);
    cr_assert_stdout_eq_str("Hello\\0aWorld!\\09\\07");
}

Test(my_showstr, non_printable_at_boundaries, .init = cr_redirect_stdout)
{
    int ret = my_showstr("\x1f \x7e\x7f");

    cr_assert_eq(ret, 0);
    cr_assert_stdout_eq_str("\\1f ~\\7f");
}
