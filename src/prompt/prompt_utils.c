/**
 * =======================================================================
 *                              PROMPT UTILS
 * =======================================================================
 * File: prompt_utils.c
 * Description: Prompt utilities for shell display.
 * Dependencies: pongsh.h
 * =======================================================================
 */

#include "../../include/pongsh.h"

char *get_current_path(void)
{
    char *current_path;

    current_path = my_malloc(PATH_MAX);
    if (!current_path) {
        return NULL;
    }
    if (getcwd(current_path, PATH_MAX) == NULL) {
        my_free(current_path);
        return NULL;
    }
    return current_path;
}

void display_fallback_prompt(void)
{
    my_printf("%spongsh%s ",
              PROMPT_USER, RESET);
}

void display_full_prompt(const char *current_path)
{
    char *relative_path;
    char *username;
    char *hostname;

    username = get_current_user();
    hostname = get_hostname();
    relative_path = get_home_relative_path(current_path);
    my_printf("%s%s%s%s@%s%s%s %s%s%s ",
              PROMPT_USER, username, RESET,
              SEPARATOR_COLOR, PROMPT_HOST, hostname, RESET,
              PROMPT_PATH, relative_path, RESET);
    my_free(relative_path);
}
