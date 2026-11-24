#include "pongsh.h"
#include "my.h"
#include <unistd.h>

static int print_env(char **env)
{
    size_t index;

    for (index = 0; env[index]; index++) {
        sh_write(STDOUT_FILENO, env[index]);
        sh_write(STDOUT_FILENO, "\n");
    }
    return 0;
}

int sh_execute(shell_t *shell, char **args)
{
    if (!my_strcmp(args[0], "exit"))
        return sh_exit(shell, args);
    if (!my_strcmp(args[0], "cd"))
        return sh_cd(shell, args);
    if (!my_strcmp(args[0], "env") && !args[1])
        return print_env(shell->env);
    if (!my_strcmp(args[0], "setenv") && !args[1])
        return print_env(shell->env);
    if (!my_strcmp(args[0], "setenv"))
        return sh_setenv(shell, args);
    if (!my_strcmp(args[0], "unsetenv"))
        return sh_unsetenv(shell, args);
    return sh_external(shell, args);
}
