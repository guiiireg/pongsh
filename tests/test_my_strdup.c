#include <criterion/criterion.h>
#include <stdlib.h>

#include "my.h"

Test(my_strdup, basic)
{
    char *copy = my_strdup("Hello");

    cr_assert_not_null(copy);
    cr_assert_str_eq(copy, "Hello");
    free(copy);
}

Test(my_strdup, empty_string)
{
    char *copy = my_strdup("");

    cr_assert_not_null(copy);
    cr_assert_str_eq(copy, "");
    free(copy);
}

Test(my_strdup, independent_copy)
{
    char *copy = my_strdup("Hello");

    cr_assert_not_null(copy);
    copy[0] = 'J';
    cr_assert_str_eq(copy, "Jello");
    free(copy);
}

Test(my_strdup, null_input)
{
    cr_assert_null(my_strdup(NULL));
}
