#include "pongsh.h"

static int valid_name(char const *name)
{
    char c;

    if (!*name || (*name >= '0' && *name <= '9'))
        return 0;
    while (*name) {
        c = *name;
        if (c != '_' && !(c >= 'a' && c <= 'z') && !(c >= 'A' && c <= 'Z')
            && !(c >= '0' && c <= '9'))
            return 0;
        name++;
    }
    return 1;
}

int sh_setenv(shell_t *shell, char **args)
{
    char const *value = "";

    if (!valid_name(args[1]) || (args[2] && args[3])) {
        sh_error("setenv", "usage: setenv NAME [VALUE]");
        return 1;
    }
    if (args[2])
        value = args[2];
    if (sh_env_set(shell, args[1], value) < 0) {
        sh_error("setenv", "out of memory");
        return 1;
    }
    return 0;
}

int sh_unsetenv(shell_t *shell, char **args)
{
    size_t index;

    if (!args[1]) {
        sh_error("unsetenv", "usage: unsetenv NAME [NAME ...]");
        return 1;
    }
    for (index = 1; args[index]; index++)
        sh_env_remove(shell, args[index]);
    return 0;
}
