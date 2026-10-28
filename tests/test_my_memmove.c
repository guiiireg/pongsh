#include <criterion/criterion.h>
#include "my.h"

Test(my_memmove, non_overlapping_areas)
{
    char dest[6] = "XXXXX";

    cr_assert_eq(my_memmove(dest, "Hello", 5), dest);
    cr_assert_str_eq(dest, "Hello");
}

Test(my_memmove, overlap_destination_after_source)
{
    char buf[10] = "abcdefghi";

    my_memmove(buf + 2, buf, 5);
    cr_assert_str_eq(buf, "ababcdehi");
}

Test(my_memmove, overlap_destination_before_source)
{
    char buf[10] = "abcdefghi";

    my_memmove(buf, buf + 2, 5);
    cr_assert_str_eq(buf, "cdefgfghi");
}

Test(my_memmove, identical_areas)
{
    char buf[6] = "Hello";

    my_memmove(buf, buf, 5);
    cr_assert_str_eq(buf, "Hello");
}

Test(my_memmove, invalid_arguments)
{
    char buf[6] = "Hello";

    cr_assert_null(my_memmove(NULL, buf, 3));
    cr_assert_null(my_memmove(buf, NULL, 3));
    cr_assert_null(my_memmove(buf, buf, -1));
}
