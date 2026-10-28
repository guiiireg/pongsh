#include <criterion/criterion.h>
#include "my.h"

Test(my_strstr, found_at_start)
{
    char str[6] = "Hello";

    cr_assert_eq(my_strstr(str, "He"), str);
}

Test(my_strstr, found_in_middle)
{
    char str[6] = "Hello";

    cr_assert_eq(my_strstr(str, "ll"), str + 2);
}

Test(my_strstr, found_at_end)
{
    char str[6] = "Hello";

    cr_assert_eq(my_strstr(str, "lo"), str + 3);
}

Test(my_strstr, not_found)
{
    cr_assert_null(my_strstr("Hello", "world"));
    cr_assert_null(my_strstr("Hello", "HelloWorld"));
}

Test(my_strstr, empty_needle)
{
    char str[6] = "Hello";

    cr_assert_eq(my_strstr(str, ""), str);
}

Test(my_strstr, null_arguments)
{
    cr_assert_null(my_strstr(NULL, "Hello"));
    cr_assert_null(my_strstr("Hello", NULL));
}
