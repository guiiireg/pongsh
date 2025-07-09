/**
 * =======================================================================
 *                              PONGSH - SHELL LOOP
 * =======================================================================
 * File: shell.c
 * Description: Main shell loop for the PONGSH shell.
 * Dependencies: pongsh.h, unistd.h
 * =======================================================================
 */
#include "../include/pongsh.h"
#include <unistd.h>
#include <limits.h>

#ifndef PATH_MAX
    #define PATH_MAX 4096
#endif

void display_prompt(void)
{
    char *current_path;

    current_path = my_malloc(PATH_MAX);
    if (!current_path) {
        my_printf("pongsh$ ");
        return;
    }
    if (getcwd(current_path, PATH_MAX) == NULL) {
        my_printf("pongsh$ ");
        my_free(current_path);
        return;
    }

    my_printf("pongsh:%s$ ", current_path);
    my_free(current_path);
}
void shell_loop(void)
{
    char *input;
    int should_exit = 0;

    while (!should_exit) {
        display_prompt();
        input = read_input();
        if (!input) {
            break;
        }
        should_exit = execute_command(input);
        my_free(input);
    }
}
