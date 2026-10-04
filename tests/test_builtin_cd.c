#include <criterion/criterion.h>
#include "../include/shell.h"

Test(builtin_cd, valid_directory)
{
    shell_t shell = {1, 0};
    char *argv[] = {"cd", "/tmp", NULL};

    cr_assert_eq(check_builtins(&shell, argv), SUCCESS);
    cr_assert_eq(shell.exit_code, 0);
}

Test(builtin_cd, invalid_directory)
{
    shell_t shell = {1, 0};
    char *argv[] = {"cd", "/nonexistent_dir_12345", NULL};

    cr_assert_eq(check_builtins(&shell, argv), FAILURE);
    cr_assert_eq(shell.exit_code, 1);
}

Test(builtin_cd, too_many_arguments)
{
    shell_t shell = {1, 0};
    char *argv[] = {"cd", "dir1", "dir2", NULL};

    cr_assert_eq(check_builtins(&shell, argv), FAILURE);
    cr_assert_eq(shell.exit_code, 1);
}

Test(builtin_cd, home_directory)
{
    shell_t shell = {1, 0};
    char *argv[] = {"cd", NULL};

    cr_assert_eq(check_builtins(&shell, argv), SUCCESS);
    cr_assert_eq(shell.exit_code, 0);
}
