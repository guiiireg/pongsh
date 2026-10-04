#include "../../include/shell.h"

int shell_loop(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read_bytes = 0;

    display_prompt();
    read_bytes = getline(&line, &len, stdin);
    while (read_bytes != -1) {
        display_prompt();
        read_bytes = getline(&line, &len, stdin);
    }
    free(line);
    return (SUCCESS);
}
