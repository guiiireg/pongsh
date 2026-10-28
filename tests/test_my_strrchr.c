#include <criterion/criterion.h>
#include "my.h"

Test(my_strrchr, found)
{
    char str[6] = "Hello";

    cr_assert_eq(my_strrchr(str, 'l'), str + 3);
    cr_assert_str_eq(my_strrchr(str, 'l'), "lo");
}

Test(my_strrchr, single_occurrence)
{
    char str[6] = "Hello";

    cr_assert_eq(my_strrchr(str, 'e'), str + 1);
}

Test(my_strrchr, not_found)
{
    cr_assert_null(my_strrchr("Hello", 'z'));
}

Test(my_strrchr, null_byte)
{
    char str[6] = "Hello";

    cr_assert_eq(my_strrchr(str, '\0'), str + 5);
}

Test(my_strrchr, null_input)
{
    cr_assert_null(my_strrchr(NULL, 'a'));
}
