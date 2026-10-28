#include <criterion/criterion.h>
#include "my.h"

Test(my_strncpy, exact_length)
{
    char dest[6] = "XXXXX";

    cr_assert_eq(my_strncpy(dest, "Hello", 5), dest);
    cr_assert_str_eq(dest, "Hello");
}

Test(my_strncpy, padding_with_null_bytes)
{
    char dest[6] = "XXXXX";

    my_strncpy(dest, "Hi", 5);
    cr_assert_str_eq(dest, "Hi");
    cr_assert_eq(dest[2], '\0');
    cr_assert_eq(dest[4], '\0');
}

Test(my_strncpy, truncation)
{
    char dest[3] = "XX";

    my_strncpy(dest, "Hello", 2);
    cr_assert_eq(dest[0], 'H');
    cr_assert_eq(dest[1], 'e');
}

Test(my_strncpy, zero_length)
{
    char dest[6] = "Hello";

    my_strncpy(dest, "Hi", 0);
    cr_assert_str_eq(dest, "Hello");
}

Test(my_strncpy, invalid_arguments)
{
    char dest[6] = "XXXXX";

    cr_assert_null(my_strncpy(NULL, "Hello", 3));
    cr_assert_null(my_strncpy(dest, NULL, 3));
    cr_assert_null(my_strncpy(dest, "Hello", -1));
}
