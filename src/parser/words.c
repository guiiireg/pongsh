#include "pongsh.h"

static int is_space(char byte)
{
    return byte == ' ' || byte == '\t' || byte == '\r';
}

static int is_boundary(char byte)
{
    return !byte || is_space(byte) || byte == ';';
}

static int copy_quoted(char **input, char **output)
{
    char quote = **input;

    (*input)++;
    while (**input && **input != quote) {
        if (quote == '"' && **input == '\\'
            && ((*input)[1] == '"' || (*input)[1] == '\\'))
            (*input)++;
        **output = **input;
        (*output)++;
        (*input)++;
    }
    if (!**input)
        return -1;
    (*input)++;
    return 0;
}

static int copy_part(char **input, char **output)
{
    char byte = **input;

    if (byte == '\'' || byte == '"')
        return copy_quoted(input, output);
    if (byte == '|' || byte == '<' || byte == '>' || byte == '&')
        return -1;
    if (byte == '\\')
        (*input)++;
    if (!**input)
        return -1;
    **output = **input;
    (*output)++;
    (*input)++;
    return 0;
}

static int copy_word(char **cursor, char **output)
{
    while (!is_boundary(**cursor)) {
        if (copy_part(cursor, output) < 0)
            return -1;
    }
    return 0;
}

static int parse_argument(char **cursor)
{
    char *out = *cursor;
    int last;

    if (copy_word(cursor, &out) < 0) {
        sh_error("pongsh", "invalid syntax or unsupported operator");
        return -1;
    }
    last = **cursor == ';';
    if (**cursor)
        (*cursor)++;
    *out = '\0';
    return last;
}

int sh_parse_next(shell_parser_t *parser)
{
    size_t count = 0;
    int result = 0;

    while (*parser->cursor && !result) {
        if (*parser->cursor == ';') {
            parser->cursor++;
            break;
        }
        if (is_space(*parser->cursor)) {
            parser->cursor++;
            continue;
        }
        parser->args[count] = parser->cursor;
        count++;
        result = parse_argument(&parser->cursor);
    }
    parser->args[count] = NULL;
    return result;
}
