#include "pongsh.h"
#include "my.h"
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static char *read_cwd(void)
{
    size_t capacity = SH_INITIAL_CWD;
    char *path;

    while (capacity <= SIZE_MAX / 2) {
        path = malloc(capacity);
        if (!path)
            return NULL;
        if (getcwd(path, capacity))
            return path;
        if (errno != ERANGE) {
            free(path);
            return NULL;
        }
        free(path);
        capacity *= 2;
    }
    return NULL;
}

static int update_paths(shell_t *shell, char *old, int print_path)
{
    char *current = read_cwd();
    int error = 0;

    if (old)
        error |= sh_env_set(shell, "OLDPWD", old) < 0;
    if (current)
        error |= sh_env_set(shell, "PWD", current) < 0;
    if (current && print_path) {
        sh_write(STDOUT_FILENO, current);
        sh_write(STDOUT_FILENO, "\n");
    }
    free(current);
    if (error)
        sh_error("cd", "out of memory");
    return error;
}

static char const *cd_target(shell_t *shell, char **args, int *print_path)
{
    if (!args[1])
        return sh_env_get(shell->env, "HOME");
    if (!my_strcmp(args[1], "-")) {
        *print_path = 1;
        return sh_env_get(shell->env, "OLDPWD");
    }
    return args[1];
}

int sh_cd(shell_t *shell, char **args)
{
    int print_path = 0;
    char const *target = cd_target(shell, args, &print_path);
    char *old;
    int result = 1;

    if (args[1] && args[2]) {
        sh_error("cd", "too many arguments");
        return 1;
    }
    if (!target) {
        sh_error("cd", print_path ? "OLDPWD not set" : "HOME not set");
        return 1;
    }
    old = read_cwd();
    if (chdir(target) < 0)
        perror(target);
    else
        result = update_paths(shell, old, print_path);
    free(old);
    return result;
}
