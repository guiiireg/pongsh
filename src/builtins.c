// ============================
//          BUILTINS
// ============================
// Made by Guireg on 17/08/2025
// Last update: 17/08/2025
// ============================
#include "../include/pongsh.h"

int pongsh_exit(char **args)
{
    (void)args;
    my_printf("Goodbye from pongsh!\n");
    return 0;
}

int pongsh_help(char **args)
{
    (void)args;
    my_printf("pongsh - A simple shell\n");
    my_printf("Available commands:\n");
    my_printf("  help - Show this help message\n");
    my_printf("  exit - Exit the shell\n");
    my_printf("  ls [path] - List directory contents\n");
    my_printf("  cat <file> - Display file information\n");
    my_printf("  cd <directory> - Change directory\n");
    my_printf("  pwd - Print working directory\n");
    my_printf("  clear - Clear the terminal screen\n");
    return 1;
}

int pongsh_pwd(char **args)
{
    char *cwd = getcwd(NULL, 0);

    (void)args;
    if (cwd == NULL) {
        my_printf("pongsh: pwd: error getting current directory\n");
        return 1;
    }
    my_printf("%s\n", cwd);
    free(cwd);
    return 1;
}

int pongsh_cd(char **args)
{
    if (args[1] == NULL) {
        my_printf("pongsh: cd: missing argument\n");
        return 1;
    }
    if (chdir(args[1]) != 0) {
        my_printf("pongsh: cd: %s: No such file or directory\n", args[1]);
        return 1;
    }
    return 1;
}

int pongsh_clear(char **args)
{
    (void)args;
    write(1, "\033[2J\033[H", 7);
    return 1;
}
