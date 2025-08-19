// ============================
//       BUILTIN_ECHO
// ============================
// Made by Guireg on 17/08/2025
// Last update: 17/08/2025
// ============================
#include "../../include/pongsh.h"

int pongsh_echo(char **args)
{
    int i = 1;

    if (args[1] == NULL) {
        my_printf("\n");
        return 1;
    }
    while (args[i] != NULL) {
        my_printf("%s", args[i]);
        if (args[i + 1] != NULL) {
            my_printf(" ");
        }
        i++;
    }
    my_printf("\n");
    return 1;
}
