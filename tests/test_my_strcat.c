#include <criterion/criterion.h>
#include "my.h"

Test(my_strcat, basic)
{
    char dest[11] = "Hello";

    cr_assert_eq(my_strcat(dest, "World"), dest);
    cr_assert_str_eq(dest, "HelloWorld");
}

Test(my_strcat, empty_source)
{
    char dest[6] = "Hello";

    my_strcat(dest, "");
    cr_assert_str_eq(dest, "Hello");
}

Test(my_strcat, empty_destination)
{
    char dest[6] = "";

    my_strcat(dest, "Hello");
    cr_assert_str_eq(dest, "Hello");
}

Test(my_strcat, null_arguments)
{
    char dest[11] = "Hello";

    cr_assert_null(my_strcat(NULL, "Hello"));
    cr_assert_null(my_strcat(dest, NULL));
}
