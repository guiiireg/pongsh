#include <criterion/criterion.h>
#include "../include/my.h"

Test(my_str_isprintable, printable_strings)
{
    cr_assert_eq(my_str_isprintable("Hello, World! 42"), 1);
    cr_assert_eq(my_str_isprintable(" "), 1);
    cr_assert_eq(my_str_isprintable("~"), 1);
    cr_assert_eq(my_str_isprintable("0123456789"), 1);
    cr_assert_eq(my_str_isprintable("!@#$%^&*()_+-=[]{}|;':,.<>/?`~"), 1);
}

Test(my_str_isprintable, empty_string)
{
    cr_assert_eq(my_str_isprintable(""), 1);
}

Test(my_str_isprintable, containing_control_characters)
{
    cr_assert_eq(my_str_isprintable("Hello\nWorld"), 0);
    cr_assert_eq(my_str_isprintable("Hello\tWorld"), 0);
    cr_assert_eq(my_str_isprintable("Hello\rWorld"), 0);
    cr_assert_eq(my_str_isprintable("\033"), 0);
    cr_assert_eq(my_str_isprintable("\n"), 0);
    cr_assert_eq(my_str_isprintable("\t"), 0);
}

Test(my_str_isprintable, ascii_boundary_characters)
{
    cr_assert_eq(my_str_isprintable("\037"), 0);
    cr_assert_eq(my_str_isprintable(" "), 1);
    cr_assert_eq(my_str_isprintable("~"), 1);
    cr_assert_eq(my_str_isprintable("\177"), 0);
    cr_assert_eq(my_str_isprintable("Hello\037"), 0);
    cr_assert_eq(my_str_isprintable("Hello\177"), 0);
}
