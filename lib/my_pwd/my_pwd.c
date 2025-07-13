/**
 * ===================================================================
 *                              MY_PWD CORE
 * ===================================================================
 * File: my_pwd.c
 * Description: Core implementation of my_pwd builtin command that
 *              displays the absolute path of the current directory.
 * Dependencies: my_pwd.h
 * ===================================================================
 */

#include "../../include/my_pwd.h"

int my_pwd(void)
{
    char *current_path;

    current_path = my_malloc(PATH_MAX);
    if (!current_path) {
                my_printf("%s%s %smy_pwd: memory allocation failed%s\n",
                  ERROR_COLOR, CROSS_MARK, RESET, RESET);
        return -1;
    }
    if (getcwd(current_path, PATH_MAX) == NULL) {
                my_printf("%s%s %smy_pwd: error getting current directory%s\n",
                  ERROR_COLOR, CROSS_MARK, RESET, RESET);
        my_free(current_path);
        return -1;
    }
        my_printf("%s%s %s%s%s%s\n",
              INFO_COLOR, FOLDER, RESET,
              PROMPT_PATH, current_path, RESET);
    my_free(current_path);
    return 0;
}
