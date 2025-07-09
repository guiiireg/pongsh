/**
 * ===================================================================
 *                              MY_CD CORE
 * ===================================================================
 * File: my_cd.c
 * Description: Core implementation of my_cd builtin command with
 *              basic functionality similar to Unix cd command.
 * Dependencies: my_cd.h
 * ===================================================================
 */

#include "../../include/my_cd.h"

int my_cd(const char *path)
{
    char *target_path;
    int result;

    target_path = resolve_cd_path(path);
    if (!target_path) {
        return -1;
    }
    if (validate_directory(target_path) != 0) {
        my_free(target_path);
        return -1;
    }
    result = change_to_directory(target_path);
    if (result == 0) {
        update_pwd_env(target_path);
    }
    my_free(target_path);
    return result;
}
