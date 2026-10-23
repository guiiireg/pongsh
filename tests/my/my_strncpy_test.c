#include <criterion/criterion.h>
#include "my/my.h"

Test(my_strncpy, copies_at_most_n_chars_without_terminating)
{
    char dest[16] = "AAAAAAAA";

    my_strncpy(dest, "hello", 3);
    cr_assert_eq(dest[0], 'h');
    cr_assert_eq(dest[1], 'e');
    cr_assert_eq(dest[2], 'l');
    cr_assert_eq(dest[3], 'A');
}

Test(my_strncpy, pads_with_nulls_when_src_is_shorter)
{
    char dest[16] = "AAAAAAAA";

    my_strncpy(dest, "hello", 8);
    cr_assert_str_eq(dest, "hello");
    cr_assert_eq(dest[7], '\0');
}

Test(my_strncpy, copies_exact_length_without_terminating)
{
    char dest[16] = "AAAAAAAA";

    my_strncpy(dest, "hello", 5);
    cr_assert_eq(dest[4], 'o');
    cr_assert_eq(dest[5], 'A');
}

Test(my_strncpy, copies_nothing_when_n_is_zero)
{
    char dest[16] = "AAAAAAAA";

    cr_assert_eq(my_strncpy(dest, "hello", 0), dest);
    cr_assert_eq(dest[0], 'A');
}

Test(my_strncpy, copies_string_shorter_than_n)
{
    char dest[16] = "AAAAAAAA";

    my_strncpy(dest, "hi", 4);
    cr_assert_str_eq(dest, "hi");
    cr_assert_eq(dest[4], 'A');
}
