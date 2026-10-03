#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/my.h"

Test(my_showmem, null_or_invalid_size, .init = cr_redirect_stdout)
{
    cr_assert_eq(my_showmem(0, 10), 0);
    cr_assert_eq(my_showmem("test", 0), 0);
    cr_assert_eq(my_showmem("test", -5), 0);
    cr_assert_stdout_eq_str("");
}

Test(my_showmem, exact_sixteen_bytes, .init = cr_redirect_stdout)
{
    const char data[] = "0123456789abcdef";
    int ret = my_showmem(data, 16);

    cr_assert_eq(ret, 0);
    cr_assert_stdout_eq_str("00000000: 3031 3233 3435 3637 3839 6162 6364 6566 0123456789abcdef\n");
}

Test(my_showmem, partial_line, .init = cr_redirect_stdout)
{
    const char data[] = "Hello";
    int ret = my_showmem(data, 5);

    cr_assert_eq(ret, 0);
    cr_assert_stdout_eq_str("00000000: 4865 6c6c 6f                            Hello\n");
}

Test(my_showmem, non_printable_chars, .init = cr_redirect_stdout)
{
    const char data[] = "\x01\x02\x03\x04\x05";
    int ret = my_showmem(data, 5);

    cr_assert_eq(ret, 0);
    cr_assert_stdout_eq_str("00000000: 0102 0304 05                            .....\n");
}
