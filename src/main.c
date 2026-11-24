#include "pongsh.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

static int parse_commands(shell_parser_t *parser)
{
    while (*parser->cursor) {
        if (sh_parse_next(parser) < 0)
            return -1;
        if (!parser->args[0])
            continue;
        while (*parser->args)
            parser->args++;
        parser->args++;
    }
    return 0;
}

static int run_commands(shell_t *shell, char **args, char **end)
{
    while (args < end && shell->running) {
        shell->status = sh_execute(shell, args);
        while (*args)
            args++;
        args++;
    }
    return shell->status;
}

static int run_line(shell_t *shell, char *line)
{
    shell_parser_t parser = {.cursor = line};
    size_t length = sh_length(line);
    char **args;
    int status = 2;

    if (length >= SIZE_MAX / sizeof(*parser.args))
        return 1;
    args = malloc((length + 1) * sizeof(*args));
    if (!args) {
        sh_error("pongsh", "out of memory");
        return 1;
    }
    parser.args = args;
    if (parse_commands(&parser) == 0)
        status = run_commands(shell, args, parser.args);
    free(args);
    return status;
}

static void shell_loop(shell_t *shell)
{
    char *line = NULL;
    int result = 0;

    while (shell->running) {
        if (shell->interactive)
            sh_write(STDOUT_FILENO, "pongsh$ ");
        result = sh_read_line(&line);
        if (result <= 0)
            break;
        shell->status = run_line(shell, line);
        free(line);
    }
    if (result < 0)
        shell->status = 1;
}

int main(int argc, char **argv, char **env)
{
    shell_t shell = {.running = 1};

    (void)argv;
    if (argc != 1) {
        sh_error("pongsh", "usage: pongsh");
        return 2;
    }
    shell.env = sh_env_copy(env);
    if (!shell.env) {
        sh_error("pongsh", "out of memory");
        return 1;
    }
    shell.interactive = isatty(STDIN_FILENO);
    if (shell.interactive) {
        signal(SIGINT, sh_interrupt);
        signal(SIGQUIT, SIG_IGN);
    }
    shell_loop(&shell);
    sh_env_free(shell.env);
    return shell.status;
}
