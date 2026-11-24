#include "my_ls.h"
#include <unistd.h>

static int set_option(ls_options_t *options, char flag)
{
    char const keys[] = "alRdrt";
    int *values[] = {&options->all, &options->long_format,
        &options->recursive, &options->directory, &options->reverse,
        &options->by_time};
    size_t index;

    for (index = 0; keys[index]; index++) {
        if (keys[index] == flag) {
            *values[index] = 1;
            return 0;
        }
    }
    return -1;
}

static int read_flags(ls_options_t *options, char const *flags)
{
    char const message[] = "my_ls: invalid option -- '";
    char const end[] = "'\n";

    while (*flags) {
        if (set_option(options, *flags) < 0) {
            (void)write(STDERR_FILENO, message, sizeof(message) - 1);
            (void)write(STDERR_FILENO, flags, 1);
            (void)write(STDERR_FILENO, end, sizeof(end) - 1);
            return -1;
        }
        flags++;
    }
    return 0;
}

int ls_parse_options(int argc, char **argv, ls_options_t *options)
{
    int count = 0;
    int parsing = 1;
    char *arg;
    int index;

    for (index = 1; index < argc; index++) {
        arg = argv[index];
        if (parsing && arg[0] == '-' && arg[1] == '-' && !arg[2]) {
            parsing = 0;
            continue;
        }
        if (!parsing || arg[0] != '-' || !arg[1]) {
            count++;
            argv[count] = arg;
            continue;
        }
        if (read_flags(options, arg + 1) < 0)
            return -1;
    }
    return count;
}
