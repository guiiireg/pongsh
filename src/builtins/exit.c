#include "pongsh.h"

static int exit_code(char const *text, int *code)
{
    unsigned int value = 0;
    int negative = *text == '-';

    if (*text == '+' || *text == '-')
        text++;
    if (!*text)
        return -1;
    while (*text >= '0' && *text <= '9') {
        value = (value * 10u + (unsigned int)(*text - '0')) & SH_STATUS_MASK;
        text++;
    }
    if (*text)
        return -1;
    if (negative)
        value = (0u - value) & SH_STATUS_MASK;
    *code = (int)value;
    return 0;
}

int sh_exit(shell_t *shell, char **args)
{
    int code = shell->status;

    if (args[1] && exit_code(args[1], &code) < 0) {
        sh_error("exit", "numeric argument required");
        shell->running = 0;
        return 2;
    }
    if (args[1] && args[2]) {
        sh_error("exit", "too many arguments");
        return 1;
    }
    shell->running = 0;
    return code;
}
