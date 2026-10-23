#include <criterion/criterion.h>
#include "my/my.h"

Test(my_strncat, appends_at_most_n_chars)
{
    char dest[8] = "foo";

    cr_assert_eq(my_strncat(dest, "barbaz", 3), dest);
    cr_assert_str_eq(dest, "foobar");
    cr_assert_eq(dest[6], '\0');
}

Test(my_strncat, appends_shorter_src_entirely)
{
    char dest[8] = "foo";

    my_strncat(dest, "ba", 5);
    cr_assert_str_eq(dest, "fooba");
}

Test(my_strncat, appends_nothing_when_n_is_zero)
{
    char dest[8] = "foo";

    my_strncat(dest, "bar", 0);
    cr_assert_str_eq(dest, "foo");
}
