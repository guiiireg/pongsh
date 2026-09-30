#include <criterion/criterion.h>
#include "../include/my.h"

Test(my_str_isalpha, alphabetical_strings)
{
    cr_assert_eq(my_str_isalpha("hello"), 1);
    cr_assert_eq(my_str_isalpha("WORLD"), 1);
    cr_assert_eq(my_str_isalpha("HelloWorld"), 1);
    cr_assert_eq(my_str_isalpha("a"), 1);
    cr_assert_eq(my_str_isalpha("Z"), 1);
}

Test(my_str_isalpha, empty_string)
{
    cr_assert_eq(my_str_isalpha(""), 1);
}

Test(my_str_isalpha, containing_digits)
{
    cr_assert_eq(my_str_isalpha("hello42"), 0);
    cr_assert_eq(my_str_isalpha("42"), 0);
    cr_assert_eq(my_str_isalpha("1337world"), 0);
}

Test(my_str_isalpha, containing_spaces_and_newlines)
{
    cr_assert_eq(my_str_isalpha("hello world"), 0);
    cr_assert_eq(my_str_isalpha(" "), 0);
    cr_assert_eq(my_str_isalpha("Hello\nWorld"), 0);
    cr_assert_eq(my_str_isalpha("Hello\tWorld"), 0);
}

Test(my_str_isalpha, containing_symbols_and_punctuation)
{
    cr_assert_eq(my_str_isalpha("Hello, World!"), 0);
    cr_assert_eq(my_str_isalpha("!@#$%^&*()"), 0);
    cr_assert_eq(my_str_isalpha("foo-bar"), 0);
}

Test(my_str_isalpha, ascii_boundary_characters)
{
    cr_assert_eq(my_str_isalpha("@"), 0);
    cr_assert_eq(my_str_isalpha("["), 0);
    cr_assert_eq(my_str_isalpha("`"), 0);
    cr_assert_eq(my_str_isalpha("{"), 0);
}
