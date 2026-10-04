#include <criterion/criterion.h>
#include "../include/shell.h"

Test(is_empty_line, null_string)
{
    cr_assert_eq(is_empty_line(NULL), 1);
}

Test(is_empty_line, empty_and_spaces)
{
    cr_assert_eq(is_empty_line(""), 1);
    cr_assert_eq(is_empty_line("   \t  \n"), 1);
}

Test(is_empty_line, valid_command)
{
    cr_assert_eq(is_empty_line("ls"), 0);
    cr_assert_eq(is_empty_line("  echo hello "), 0);
}
