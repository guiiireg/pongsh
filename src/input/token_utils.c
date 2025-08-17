// ============================
//        TOKEN_UTILS
// ============================
// Made by Guireg on 17/08/2025
// Last update: 17/08/2025
// ============================
#include "../include/pongsh.h"

void skip_whitespace(char *line, int *i)
{
    while (line[*i] == ' ' || line[*i] == '\t') {
        (*i)++;
    }
}

int find_word_end(char *line, int start)
{
    int i = start;

    while (line[i] != '\0' && line[i] != ' ' && line[i] != '\t') {
        i++;
    }
    return i;
}

char *create_token(char *line, int start, int end)
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
