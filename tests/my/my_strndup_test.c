#include <criterion/criterion.h>
#include <stdlib.h>
#include "my/my.h"

Test(my_strndup, truncates_longer_string)
{
    char *copy = my_strndup("truncate me", 4);

    cr_assert_not_null(copy);
    cr_assert_str_eq(copy, "trun");
    free(copy);
}

Test(my_strndup, copies_shorter_string_entirely)
{
    char *copy = my_strndup("hi", 10);

    cr_assert_not_null(copy);
    cr_assert_str_eq(copy, "hi");
    free(copy);
}

Test(my_strndup, zero_n_gives_empty_string)
{
    char *copy = my_strndup("hello", 0);

    cr_assert_not_null(copy);
    cr_assert_eq(copy[0], '\0');
    free(copy);
}
