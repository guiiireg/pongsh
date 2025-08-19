// ============================
//     COMMAND_EXECUTOR
// ============================
// Made by Guireg on 17/08/2025
// Last update: 17/08/2025
// ============================
#include "../include/pongsh.h"

static const builtin_t builtins[] = {
    {"exit", &pongsh_exit},
    {"help", &pongsh_help},
    {"ls", &pongsh_ls},
    {"cat", &pongsh_cat},
    {"cd", &pongsh_cd},
    {"pwd", &pongsh_pwd},
    {"clear", &pongsh_clear},
    {"history", &pongsh_history},
    {"echo", &pongsh_echo},
    {"env", &pongsh_env},
    {"which", &pongsh_which}
};

int num_builtins(void)
{
    return sizeof(builtins) / sizeof(builtin_t);
}

int execute_command(char **args)
{
    if (args[0] == NULL) {
        return 1;
    }
    if (is_builtin(args[0])) {
        return call_builtin(args);
    }
    my_printf("pongsh: %s: command not found\n", args[0]);
    return 1;
}

int is_builtin(char *command)
{
    for (int i = 0; i < num_builtins(); i++) {
        if (my_strcmp(command, builtins[i].name) == 0) {
            return 1;
        }
    }
    return 0;
}

int call_builtin(char **args)
{
    for (int i = 0; i < num_builtins(); i++) {
        if (my_strcmp(args[0], builtins[i].name) == 0) {
            return builtins[i].func(args);
        }
    }
    return 1;
}

void free_args(char **args)
{
    int i = 0;

    if (args == NULL) {
        return;
    }
    while (args[i] != NULL) {
        free(args[i]);
        i++;
    }
    free(args);
}
