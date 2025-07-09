/**
 * ===================================================================
 *                              CD UTILITIES
 * ===================================================================
 * File: cd_utils.c
 * Description: Utility functions for my_cd implementation including
 *              path resolution, validation, and environment handling.
 * Dependencies: my_cd.h
 * ===================================================================
 */

#include "../../include/my_cd.h"

static char *get_home_directory(void)
{
    char *home;

    home = getenv("HOME");
    if (!home) {
        my_printf("my_cd: HOME environment variable not set\n");
        return NULL;
    }
    return my_strdup(home);
}

int validate_directory(const char *path)
{
    struct stat file_stat;

    if (!path) {
        my_printf("my_cd: path is null\n");
        return -1;
    }
    if (stat(path, &file_stat) == -1) {
        my_printf("my_cd: %s: No such file or directory\n", path);
        return -1;
    }
    if (!S_ISDIR(file_stat.st_mode)) {
        my_printf("my_cd: %s: Not a directory\n", path);
        return -1;
    }
    return 0;
}

char *resolve_cd_path(const char *path)
{
    char *resolved_path;

    if (!path || my_strlen(path) == 0) {
        return get_home_directory();
    }
    if (my_strcmp(path, "~") == 0) {
        return get_home_directory();
    }
    resolved_path = my_strdup(path);
    if (!resolved_path) {
        my_printf("my_cd: memory allocation failed\n");
        return NULL;
    }
    return resolved_path;
}

char *get_current_directory(void)
{
    char *buffer;

    buffer = my_malloc(PATH_MAX);
    if (!buffer) {
        return NULL;
    }
    if (getcwd(buffer, PATH_MAX) == NULL) {
        my_free(buffer);
        return NULL;
    }
    return buffer;
}

void update_pwd_env(const char *new_path)
{
    char *current_dir;

    if (!new_path) {
        current_dir = get_current_directory();
        if (current_dir) {
            setenv("PWD", current_dir, 1);
            my_free(current_dir);
        }
    } else {
        setenv("PWD", new_path, 1);
    }
}

int change_to_directory(const char *path)
{
    if (chdir(path) == -1) {
        my_printf("my_cd: %s: Permission denied or path error\n", path);
        return -1;
    }
    return 0;
}
