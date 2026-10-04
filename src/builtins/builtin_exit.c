#include "../../include/shell.h"

static int is_number(const char *str)
{
    size_t i = 0;

    if (str == NULL || str[0] == '\0')
        return (0);
    if (str[0] == '+' || str[0] == '-')
        i++;
    if (str[i] == '\0')
        return (0);
    while (str[i] != '\0') {
        if (str[i] < '0' || str[i] > '9')
            return (0);
        i++;
    }
    return (1);
}

int builtin_exit(shell_t *shell, char **argv)
{
    if (argv[1] == NULL) {
        shell->is_running = 0;
        return (shell->exit_code);
    }
    if (!is_number(argv[1])) {
        write(STDERR_FILENO, "exit: Expression Syntax.\n", 25);
        shell->exit_code = 1;
        return (FAILURE);
    }
    shell->is_running = 0;
    shell->exit_code = atoi(argv[1]);
    return (shell->exit_code);
}

int check_builtins(shell_t *shell, char **argv)
{
    if (strcmp(argv[0], "exit") == 0)
        return (builtin_exit(shell, argv));
    if (strcmp(argv[0], "cd") == 0)
        return (builtin_cd(shell, argv));
    return (-1);
}
