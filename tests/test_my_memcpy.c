#include <criterion/criterion.h>
#include "my.h"

Test(my_memcpy, copies_bytes)
{
    char dest[6] = "XXXXX";

    cr_assert_eq(my_memcpy(dest, "Hello", 5), dest);
    cr_assert_str_eq(dest, "Hello");
}

Test(my_memcpy, copies_non_string_data)
{
    int dest[3] = {0, 0, 0};
    int src[3] = {1, 2, 3};

    my_memcpy(dest, src, (int)sizeof(src));
    cr_assert_eq(dest[0], 1);
    cr_assert_eq(dest[1], 2);
    cr_assert_eq(dest[2], 3);
}

Test(my_memcpy, zero_length)
{
    char dest[6] = "XXXXX";

    cr_assert_eq(my_memcpy(dest, "Hello", 0), dest);
    cr_assert_str_eq(dest, "XXXXX");
}

Test(my_memcpy, invalid_arguments)
{
    char dest[6] = "XXXXX";

    cr_assert_null(my_memcpy(NULL, "Hello", 3));
    cr_assert_null(my_memcpy(dest, NULL, 3));
    cr_assert_null(my_memcpy(dest, "Hello", -1));
}
