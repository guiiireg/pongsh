#include <criterion/criterion.h>
#include "my.h"

Test(my_strcpy, basic)
{
    char dest[6] = "XXXXX";

    cr_assert_eq(my_strcpy(dest, "Hello"), dest);
    cr_assert_str_eq(dest, "Hello");
}

Test(my_strcpy, empty_string)
{
    char dest[6] = "XXXXX";

    cr_assert_eq(my_strcpy(dest, ""), dest);
    cr_assert_str_eq(dest, "");
}

Test(my_strcpy, null_destination)
{
    cr_assert_null(my_strcpy(NULL, "Hello"));
}

Test(my_strcpy, null_source)
{
    char dest[6];

    cr_assert_null(my_strcpy(dest, NULL));
}
