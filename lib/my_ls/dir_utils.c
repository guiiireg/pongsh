/**
 * ===================================================================
 *                              MY_LS DIR UTILS
 * ===================================================================
 * File: dir_utils.c
 * Description: Directory opening logic for my_ls implementation.
 * Dependencies: my_ls.h
 * ===================================================================
 */
#include "../../include/my_ls.h"

DIR *open_directory(const char *dir_path)
{
    DIR *dir;

    dir = opendir(dir_path);
    if (!dir) {
        my_printf(
            "my_ls: cannot access '%s': No such file or directory\n",
            dir_path
        );
    }
    return dir;
}
