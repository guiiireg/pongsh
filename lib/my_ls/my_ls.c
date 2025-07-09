/**
 * ===================================================================
 *                              MY_LS CORE
 * ===================================================================
 * File: my_ls.c
 * Description: Core implementation of my_ls builtin command with
 *              basic functionality similar to Unix ls command.
 * Dependencies: my_ls.h
 * ===================================================================
 */

#include "../../include/my_ls.h"

int my_ls(const char *path)
{
    DIR *dir;
    const char *dir_path = path ? path : ".";

    dir = open_directory(dir_path);
    if (!dir) {
        return -1;
    }
    process_directory_entries(dir, dir_path, 0, 0);
    closedir(dir);
    return 0;
}

int my_ls_with_flags(const char *path, const char *flags)
{
    DIR *dir;
    const char *dir_path = path ? path : ".";
    int show_hidden = 0;
    int show_details = 0;

    parse_ls_flags(flags, &show_hidden, &show_details);
    dir = open_directory(dir_path);
    if (!dir) {
        return -1;
    }
    process_directory_entries(dir, dir_path, show_hidden, show_details);
    closedir(dir);
    return 0;
}
