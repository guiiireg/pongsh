/**
 * ============================================================================
 *                              PATH UTILS IMPLEMENTATION
 * ============================================================================
 * File: path_utils.c
 * Description: Path manipulation utilities for shell display.
 * Dependencies: colors.h
 * ============================================================================
 */

#include "../../include/colors.h"

int check_home_prefix(const char *path, const char *home_path, int home_len)
{
    int path_len;

    path_len = my_strlen(path);
    if (path_len >= home_len && my_strncmp(path, home_path, home_len) == 0) {
        return path_len;
    }
    return -1;
}

char *build_relative_path(const char *path, int home_len, int path_len)
{
    char *relative_path;

    if (path_len == home_len) {
        return my_strdup("~");
    }
    if (path[home_len] == '/') {
        relative_path = my_malloc(path_len - home_len + 2);
        if (!relative_path)
            return NULL;
        my_strcpy(relative_path, "~");
        my_strcat(relative_path, path + home_len);
        return relative_path;
    }
    return NULL;
}

char *get_home_relative_path(const char *path)
{
    char *home_path;
    char *relative_path;
    int home_len;
    int path_len;

    if (!path)
        return my_strdup("~");
    home_path = getenv("HOME");
    if (!home_path)
        return my_strdup(path);
    home_len = my_strlen(home_path);
    path_len = check_home_prefix(path, home_path, home_len);
    if (path_len != -1) {
        relative_path = build_relative_path(path, home_len, path_len);
        if (relative_path)
            return relative_path;
    }
    return my_strdup(path);
}
