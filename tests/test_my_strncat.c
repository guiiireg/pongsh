#include <criterion/criterion.h>
#include "my.h"

Test(my_strncat, basic)
{
    char dest[11] = "Hello";

    cr_assert_eq(my_strncat(dest, "World", 5), dest);
    cr_assert_str_eq(dest, "HelloWorld");
}

Test(my_strncat, limited_append)
{
    char dest[9] = "Hello";

    my_strncat(dest, "World", 3);
    cr_assert_str_eq(dest, "HelloWor");
}

Test(my_strncat, zero_length)
{
    char dest[6] = "Hello";

    my_strncat(dest, "World", 0);
    cr_assert_str_eq(dest, "Hello");
}

Test(my_strncat, null_arguments)
{
    char dest[11] = "Hello";

    cr_assert_null(my_strncat(NULL, "Hello", 3));
    cr_assert_null(my_strncat(dest, NULL, 3));
    cr_assert_null(my_strncat(dest, "World", -1));
}
