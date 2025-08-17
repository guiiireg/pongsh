// ============================
//       INPUT_PARSER
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

static void skip_whitespace(char *line, int *i)
{
    while (line[*i] == ' ' || line[*i] == '\t') {
        (*i)++;
    }
}

static int find_word_end(char *line, int start)
{
    int i = start;

    while (line[i] != '\0' && line[i] != ' ' && line[i] != '\t') {
        i++;
    }
    return i;
}

static char *create_token(char *line, int start, int end)
{
    char *token = malloc((end - start + 1) * sizeof(char));
    int j;

    if (!token) {
        my_printf("pongsh: allocation error\n");
        exit(1);
    }
    for (j = 0; j < (end - start); j++) {
        token[j] = line[start + j];
    }
    token[j] = '\0';
    return token;
}

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
