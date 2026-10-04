#include "../../include/shell.h"

static int change_directory(shell_t *shell, const char *path)
{
    if (chdir(path) == -1) {
        perror(path);
        shell->exit_code = 1;
        return (FAILURE);
    }
    shell->exit_code = 0;
    return (SUCCESS);
}

static const char *get_target_path(shell_t *shell, char **argv)
{
    const char *target = argv[1];

    if (target == NULL) {
        target = getenv("HOME");
        if (target == NULL) {
            write(STDERR_FILENO, "cd: No home directory.\n", 23);
            shell->exit_code = 1;
            return (NULL);
        }
    }
    return (target);
}

int builtin_cd(shell_t *shell, char **argv)
{
    const char *target = NULL;

    if (argv[1] != NULL && argv[2] != NULL) {
        write(STDERR_FILENO, "cd: Too many arguments.\n", 24);
        shell->exit_code = 1;
        return (FAILURE);
    }
    target = get_target_path(shell, argv);
    if (target == NULL)
        return (FAILURE);
    return (change_directory(shell, target));
}
