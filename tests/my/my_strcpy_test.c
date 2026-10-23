#include <criterion/criterion.h>
#include "my/my.h"

Test(my_strcpy, copies_string)
{
    char dest[6] = "xxxxx";

    cr_assert_eq(my_strcpy(dest, "hello"), dest);
    cr_assert_str_eq(dest, "hello");
}

Test(my_strcpy, copies_empty_string)
{
    char dest[4] = "xxx";

    my_strcpy(dest, "");
    cr_assert_eq(dest[0], '\0');
}

Test(my_strcpy, copies_and_null_terminates)
{
    char dest[8] = "xxxxxxx";

    my_strcpy(dest, "abc");
    cr_assert_eq(dest[3], '\0');
}

Test(my_strcpy, overwrites_previous_content)
{
    char dest[16] = "longer content";

    my_strcpy(dest, "hi");
    cr_assert_str_eq(dest, "hi");
}
