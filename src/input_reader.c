// ============================
//       INPUT_READER
// ============================
// Made by Guireg on 17/08/2025
// Last update: 17/08/2025
// ============================
#include "../include/pongsh.h"

static char *allocate_line(void)
{
    char *line = malloc(MAX_INPUT_SIZE);

    if (!line) {
        my_printf("pongsh: allocation error\n");
        exit(1);
    }
    return line;
}

static int read_character(char *line, int position)
{
    int c = getchar();

    if (c == EOF || c == '\n') {
        line[position] = '\0';
        return -1;
    }
    line[position] = c;
    return position + 1;
}

static int check_buffer_overflow(char *line, int position)
{
    if (position >= MAX_INPUT_SIZE) {
        my_printf("pongsh: input too long\n");
        line[MAX_INPUT_SIZE - 1] = '\0';
        return 1;
    }
    return 0;
}

char *read_line(void)
{
    char *line = allocate_line();
    int position = 0;

    while (1) {
        position = read_character(line, position);
        if (position == -1) {
            return line;
        }
        if (check_buffer_overflow(line, position)) {
            return line;
        }
    }
}
