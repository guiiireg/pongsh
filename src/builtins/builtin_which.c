// ============================
//       BUILTIN_WHICH
// ============================
// Made by Guireg on 17/08/2025
// Last update: 17/08/2025
// ============================
#include "../../include/pongsh.h"

extern char **environ;

static char *get_path_env(void)
{
    int i = 0;
    int path_len = 5;

    if (environ == NULL) {
        return NULL;
    }
    while (environ[i] != NULL) {
        if (my_strlen(environ[i]) > path_len) {
            if (environ[i][0] == 'P' && environ[i][1] == 'A' &&
                environ[i][2] == 'T' && environ[i][3] == 'H' &&
                environ[i][4] == '=') {
                return &environ[i][5];
            }
        }
        i++;
    }
    return NULL;
}

static int check_file_exists(char const *path)
{
    struct stat file_stat;

    if (stat(path, &file_stat) == 0) {
        return S_ISREG(file_stat.st_mode);
    }
    return 0;
}

static int build_command_path(char *dest, char const *dir, char const *cmd)
{
    int dir_len = my_strlen(dir);
    int cmd_len = my_strlen(cmd);
    int i;

    if (dir_len + cmd_len + 2 > 1024) {
        return -1;
    }
    for (i = 0; i < dir_len; i++) {
        dest[i] = dir[i];
    }
    if (dir_len > 0 && dir[dir_len - 1] != '/') {
        dest[i] = '/';
        i++;
    }
    for (int j = 0; j < cmd_len; j++) {
        dest[i + j] = cmd[j];
    }
    dest[i + cmd_len] = '\0';
    return 0;
}

int pongsh_which(char **args)
{
    char *path_env;
    char *path_copy;
    char *token;
    char full_path[1024];
    int i = 0;
    int start;
    int path_len;

    if (args[1] == NULL) {
        my_printf("which: missing operand\n");
        return 1;
    }
    path_env = get_path_env();
    if (path_env == NULL) {
        my_printf("which: PATH not found\n");
        return 1;
    }
    path_len = my_strlen(path_env);
    path_copy = malloc((path_len + 1) * sizeof(char));
    if (!path_copy) {
        my_printf("which: allocation error\n");
        return 1;
    }
    for (i = 0; i <= path_len; i++) {
        path_copy[i] = path_env[i];
    }
    i = 0;
    while (path_copy[i] != '\0') {
        start = i;
        while (path_copy[i] != ':' && path_copy[i] != '\0') {
            i++;
        }
        path_copy[i] = '\0';
        token = &path_copy[start];
        if (build_command_path(full_path, token, args[1]) == 0) {
            if (check_file_exists(full_path)) {
                my_printf("%s\n", full_path);
                free(path_copy);
                return 1;
            }
        }
        if (path_copy[i] == '\0') {
            break;
        }
        i++;
    }
    my_printf("which: %s: command not found\n", args[1]);
    free(path_copy);
    return 1;
}
