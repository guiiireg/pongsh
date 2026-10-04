#include <criterion/criterion.h>
#include "../include/shell.h"

Test(builtins, unknown_command)
{
    shell_t shell = {1, 0};
    char *argv[] = {"ls", "-l", NULL};

    cr_assert_eq(check_builtins(&shell, argv), -1);
}

Test(builtins, exit_no_argument)
{
    shell_t shell = {1, 10};
    char *argv[] = {"exit", NULL};

    cr_assert_eq(check_builtins(&shell, argv), 10);
    cr_assert_eq(shell.is_running, 0);
}

Test(builtins, exit_numeric_argument)
{
    shell_t shell = {1, 0};
    char *argv[] = {"exit", "42", NULL};

    cr_assert_eq(check_builtins(&shell, argv), 42);
    cr_assert_eq(shell.is_running, 0);
    cr_assert_eq(shell.exit_code, 42);
}

Test(builtins, exit_invalid_argument)
{
    shell_t shell = {1, 0};
    char *argv[] = {"exit", "invalid", NULL};

    cr_assert_eq(check_builtins(&shell, argv), FAILURE);
    cr_assert_eq(shell.is_running, 1);
    cr_assert_eq(shell.exit_code, 1);
}
