#include <criterion/criterion.h>
#include <string.h>
#include "my/my.h"

Test(my_strstr, finds_needle_in_middle)
{
    char str[32] = "find a needle here";

    cr_assert_eq(my_strstr(str, "needle"), str + 7);
}

Test(my_strstr, finds_needle_at_start)
{
    char str[32] = "find a needle here";

    cr_assert_eq(my_strstr(str, "find"), str);
}

Test(my_strstr, finds_needle_at_end)
{
    char str[32] = "find a needle here";

    cr_assert_eq(my_strstr(str, "here"), str + 14);
}

Test(my_strstr, returns_null_when_not_found)
{
    char str[32] = "find a needle here";

    cr_assert_null(my_strstr(str, "zzz"));
}

Test(my_strstr, empty_needle_returns_str)
{
    char str[32] = "find a needle here";

    cr_assert_eq(my_strstr(str, ""), str);
}

Test(my_strstr, match_is_case_sensitive)
{
    char str[32] = "find a needle here";

    cr_assert_null(my_strstr(str, "Needle"));
}
