// ============================
//        LINE_PARSER
// ============================
// Made by Guireg on 17/08/2025
// Last update: 17/08/2025
// ============================
#include "../include/pongsh.h"

char **parse_line(char *line)
{
    int position = 0;
    char **tokens = malloc(MAX_ARGS * sizeof(char *));
    int i = 0;
    int start;
    int end;

    if (!tokens) {
        my_printf("pongsh: allocation error\n");
        exit(1);
    }
    while (line[i] != '\0') {
        skip_whitespace(line, &i);
        if (line[i] == '\0') {
            break;
        }
        start = i;
        end = find_word_end(line, start);
        tokens[position] = create_token(line, start, end);
        position++;
        i = end;
        if (position >= MAX_ARGS - 1) {
            break;
        }
    }
    tokens[position] = NULL;
    return tokens;
}
