#include "../../include/shell.h"

static void strip_newline(char *str, ssize_t len)
{
    if (str != NULL && len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
}

static void handle_input(char *line, ssize_t len)
{
    char **argv = NULL;

    strip_newline(line, len);
    if (is_empty_line(line))
        return;
    argv = split_words(line);
    if (argv == NULL)
        return;
    free_word_array(argv);
}

int shell_loop(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read_bytes = 0;

    display_prompt();
    read_bytes = getline(&line, &len, stdin);
    while (read_bytes != -1) {
        handle_input(line, read_bytes);
        display_prompt();
        read_bytes = getline(&line, &len, stdin);
    }
    free(line);
    return (SUCCESS);
}
