#include <criterion/criterion.h>
#include "../include/my.h"

Test(my_str_islower, lowercase_strings)
{
    cr_assert_eq(my_str_islower("hello"), 1);
    cr_assert_eq(my_str_islower("world"), 1);
    cr_assert_eq(my_str_islower("a"), 1);
    cr_assert_eq(my_str_islower("z"), 1);
}

Test(my_str_islower, empty_string)
{
    cr_assert_eq(my_str_islower(""), 1);
}

Test(my_str_islower, containing_uppercase)
{
    cr_assert_eq(my_str_islower("HELLO"), 0);
    cr_assert_eq(my_str_islower("Hello"), 0);
    cr_assert_eq(my_str_islower("hellO"), 0);
    cr_assert_eq(my_str_islower("A"), 0);
}

Test(my_str_islower, containing_digits)
{
    cr_assert_eq(my_str_islower("hello42"), 0);
    cr_assert_eq(my_str_islower("42"), 0);
}

Test(my_str_islower, containing_spaces_and_newlines)
{
    cr_assert_eq(my_str_islower("hello world"), 0);
    cr_assert_eq(my_str_islower(" "), 0);
    cr_assert_eq(my_str_islower("hello\n"), 0);
    cr_assert_eq(my_str_islower("hello\t"), 0);
}

Test(my_str_islower, containing_symbols)
{
    cr_assert_eq(my_str_islower("hello!"), 0);
    cr_assert_eq(my_str_islower("foo-bar"), 0);
    cr_assert_eq(my_str_islower("!@#$%^&*()"), 0);
}

Test(my_str_islower, ascii_boundary_characters)
{
    cr_assert_eq(my_str_islower("`"), 0);
    cr_assert_eq(my_str_islower("{"), 0);
    cr_assert_eq(my_str_islower("`hello"), 0);
    cr_assert_eq(my_str_islower("hello{"), 0);
}
