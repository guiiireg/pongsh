#include "../../include/shell.h"

static void strip_newline(char *str, ssize_t len)
{
    if (str != NULL && len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
}

static void handle_input(shell_t *shell, char *line, ssize_t len)
{
    char **argv = NULL;

    strip_newline(line, len);
    if (is_empty_line(line))
        return;
    argv = split_words(line);
    if (argv == NULL || argv[0] == NULL)
        return;
    if (check_builtins(shell, argv) == -1)
        shell->exit_code = exec_command(argv);
    free_word_array(argv);
}

int shell_loop(void)
{
    shell_t shell = {1, 0};
    char *line = NULL;
    size_t len = 0;
    ssize_t read_bytes = 0;

    display_prompt();
    read_bytes = getline(&line, &len, stdin);
    while (shell.is_running && read_bytes != -1) {
        handle_input(&shell, line, read_bytes);
        if (shell.is_running)
            display_prompt();
        read_bytes = shell.is_running ? getline(&line, &len, stdin) : -1;
    }
    free(line);
    return (shell.exit_code);
}
