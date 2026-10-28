#include <criterion/criterion.h>
#include "my.h"

Test(my_strchr, found)
{
    char str[6] = "Hello";

    cr_assert_eq(my_strchr(str, 'H'), str);
    cr_assert_eq(my_strchr(str, 'l'), str + 2);
    cr_assert_str_eq(my_strchr(str, 'l'), "llo");
}

Test(my_strchr, not_found)
{
    cr_assert_null(my_strchr("Hello", 'z'));
}

Test(my_strchr, null_byte)
{
    char str[6] = "Hello";

    cr_assert_eq(my_strchr(str, '\0'), str + 5);
}

Test(my_strchr, null_input)
{
    cr_assert_null(my_strchr(NULL, 'a'));
}
