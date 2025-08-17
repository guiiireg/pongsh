// ============================
//       INPUT_READER
// ============================
// Made by Guireg on 17/08/2025
// Last update: 17/08/2025
// ============================
#include "../include/pongsh.h"

char *read_line(void)
{
    char *line = malloc(MAX_INPUT_SIZE);
    int position = 0;
    int c;

    if (!line) {
        my_printf("pongsh: allocation error\n");
        exit(1);
    }
    while (1) {
        c = getchar();
        if (c == EOF || c == '\n') {
            line[position] = '\0';
            return line;
        }
        line[position] = c;
        position++;
        if (position >= MAX_INPUT_SIZE) {
            my_printf("pongsh: input too long\n");
            line[MAX_INPUT_SIZE - 1] = '\0';
            return line;
        }
    }
}
