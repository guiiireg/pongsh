#include <criterion/criterion.h>
#include "../include/my.h"

Test(my_strcat, appends_src_to_dest)
{
    char dest[8] = "foo";

    cr_assert_eq(my_strcat(dest, "bar"), dest);
    cr_assert_str_eq(dest, "foobar");
}

Test(my_strcat, appends_empty_src)
{
    char dest[4] = "foo";

    my_strcat(dest, "");
    cr_assert_str_eq(dest, "foo");
}

Test(my_strcat, appends_to_empty_dest)
{
    char dest[4] = "";

    my_strcat(dest, "foo");
    cr_assert_str_eq(dest, "foo");
}
