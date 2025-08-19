// ============================
//        BUILTIN_ENV
// ============================
// Made by Guireg on 17/08/2025
// Last update: 17/08/2025
// ============================
#include "../../include/pongsh.h"

extern char **environ;

int pongsh_env(char **args)
{
    int i = 0;

    (void)args;
    if (environ == NULL) {
        my_printf("No environment variables available\n");
        return 1;
    }
    while (environ[i] != NULL) {
        my_printf("%s\n", environ[i]);
        i++;
    }
    return 1;
}
