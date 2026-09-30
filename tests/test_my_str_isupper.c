#include <criterion/criterion.h>
#include "../include/my.h"

Test(my_str_isupper, uppercase_strings)
{
    cr_assert_eq(my_str_isupper("HELLO"), 1);
    cr_assert_eq(my_str_isupper("WORLD"), 1);
    cr_assert_eq(my_str_isupper("A"), 1);
    cr_assert_eq(my_str_isupper("Z"), 1);
}

Test(my_str_isupper, empty_string)
{
    cr_assert_eq(my_str_isupper(""), 1);
}

Test(my_str_isupper, containing_lowercase)
{
    cr_assert_eq(my_str_isupper("hello"), 0);
    cr_assert_eq(my_str_isupper("Hello"), 0);
    cr_assert_eq(my_str_isupper("HELLo"), 0);
    cr_assert_eq(my_str_isupper("a"), 0);
}

Test(my_str_isupper, containing_digits)
{
    cr_assert_eq(my_str_isupper("HELLO42"), 0);
    cr_assert_eq(my_str_isupper("42"), 0);
}

Test(my_str_isupper, containing_spaces_and_newlines)
{
    cr_assert_eq(my_str_isupper("HELLO WORLD"), 0);
    cr_assert_eq(my_str_isupper(" "), 0);
    cr_assert_eq(my_str_isupper("HELLO\n"), 0);
    cr_assert_eq(my_str_isupper("HELLO\t"), 0);
}

Test(my_str_isupper, containing_symbols)
{
    cr_assert_eq(my_str_isupper("HELLO!"), 0);
    cr_assert_eq(my_str_isupper("FOO-BAR"), 0);
    cr_assert_eq(my_str_isupper("!@#$%^&*()"), 0);
}

Test(my_str_isupper, ascii_boundary_characters)
{
    cr_assert_eq(my_str_isupper("@"), 0);
    cr_assert_eq(my_str_isupper("["), 0);
    cr_assert_eq(my_str_isupper("@HELLO"), 0);
    cr_assert_eq(my_str_isupper("HELLO["), 0);
}
