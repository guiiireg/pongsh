// ============================
//         SHELL_CORE
// ============================
// Made by Guireg on 17/08/2025
// Last update: 17/08/2025
// ============================
#include "../include/pongsh.h"

int shell_loop(void)
{
    char *line;
    char **args;
    int status = 1;

    while (status) {
        my_printf(PROMPT);
        line = read_line();
        if (line == NULL) {
            break;
        }
        args = parse_line(line);
        if (args != NULL && args[0] != NULL) {
            status = execute_command(args);
        }
        free(line);
        free_args(args);
    }
    return 0;
}
