// ============================
//        BUILTIN_LS
// ============================
// Made by Guireg on 17/08/2025
// Last update: 17/08/2025
// ============================
#include "../include/pongsh.h"

static int ls_list_directory(char const *path)
{
    DIR *dir;
    struct dirent *entry;
    int count = 0;

    dir = opendir(path);
    if (dir == NULL) {
        my_printf("ls: cannot access '%s': No such file or directory\n", path);
        return -1;
    }
    entry = readdir(dir);
    while (entry != NULL) {
        if (entry->d_name[0] != '.') {
            my_printf("%s\n", entry->d_name);
            count++;
        }
        entry = readdir(dir);
    }
    closedir(dir);
    return count;
}

int pongsh_ls(char **args)
{
    char const *path = ".";

    if (args[1] != NULL) {
        path = args[1];
    }
    ls_list_directory(path);
    return 1;
}
