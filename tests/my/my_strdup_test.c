#include <criterion/criterion.h>
#include <stdlib.h>
#include "my/my.h"

Test(my_strdup, duplicates_string)
{
    char *copy = my_strdup("hello");

    cr_assert_not_null(copy);
    cr_assert_str_eq(copy, "hello");
    free(copy);
}

Test(my_strdup, duplicates_empty_string)
{
    char *copy = my_strdup("");

    cr_assert_not_null(copy);
    cr_assert_eq(copy[0], '\0');
    free(copy);
}

Test(my_strdup, copy_is_independent)
{
    char *copy = my_strdup("hello");

    copy[0] = 'H';
    cr_assert_eq(copy[0], 'H');
    free(copy);
}
