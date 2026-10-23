#include <criterion/criterion.h>
#include "my/my.h"

Test(my_strlen, counts_regular_string)
{
    cr_assert_eq(my_strlen("hello"), 5);
}

Test(my_strlen, counts_empty_string)
{
    cr_assert_eq(my_strlen(""), 0);
}

Test(my_strlen, counts_single_char)
{
    cr_assert_eq(my_strlen("a"), 1);
}

Test(my_strlen, ignores_content_after_null)
{
    cr_assert_eq(my_strlen("ab\0cd"), 2);
}
