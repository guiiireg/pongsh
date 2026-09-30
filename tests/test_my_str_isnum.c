#include <criterion/criterion.h>
#include "../include/my.h"

Test(my_str_isnum, numeric_strings)
{
    cr_assert_eq(my_str_isnum("0123456789"), 1);
    cr_assert_eq(my_str_isnum("42"), 1);
    cr_assert_eq(my_str_isnum("0"), 1);
}

Test(my_str_isnum, empty_string)
{
    cr_assert_eq(my_str_isnum(""), 1);
}

Test(my_str_isnum, containing_letters)
{
    cr_assert_eq(my_str_isnum("42hello"), 0);
    cr_assert_eq(my_str_isnum("hello42"), 0);
    cr_assert_eq(my_str_isnum("hello"), 0);
}

Test(my_str_isnum, containing_signs)
{
    cr_assert_eq(my_str_isnum("+42"), 0);
    cr_assert_eq(my_str_isnum("-42"), 0);
}

Test(my_str_isnum, containing_spaces_and_newlines)
{
    cr_assert_eq(my_str_isnum("42 42"), 0);
    cr_assert_eq(my_str_isnum(" "), 0);
    cr_assert_eq(my_str_isnum("42\n"), 0);
    cr_assert_eq(my_str_isnum("42\t"), 0);
}

Test(my_str_isnum, containing_symbols)
{
    cr_assert_eq(my_str_isnum("42.5"), 0);
    cr_assert_eq(my_str_isnum("!@#$%^&*()"), 0);
}

Test(my_str_isnum, ascii_boundary_characters)
{
    cr_assert_eq(my_str_isnum("/"), 0);
    cr_assert_eq(my_str_isnum(":"), 0);
    cr_assert_eq(my_str_isnum("42/"), 0);
    cr_assert_eq(my_str_isnum("42:"), 0);
}
