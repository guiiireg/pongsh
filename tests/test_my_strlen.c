#include <criterion/criterion.h>
#include <string.h>
#include "../include/my.h"

Test(my_strlen, standard_string)
{
    cr_assert_eq(my_strlen("Hello"), 5);
}

Test(my_strlen, empty_string)
{
    cr_assert_eq(my_strlen(""), 0);
}

Test(my_strlen, single_character)
{
    cr_assert_eq(my_strlen("x"), 1);
}

Test(my_strlen, string_with_spaces_and_special)
{
    const char *str = "Hello, World! 123\t\n";

    cr_assert_eq(my_strlen(str), (int)strlen(str));
}

Test(my_strlen, long_string)
{
    const char *str = "The quick brown fox jumps over the lazy dog";

    cr_assert_eq(my_strlen(str), (int)strlen(str));
}
