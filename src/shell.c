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

    current_path = get_current_path();
    if (!current_path) {
        display_fallback_prompt();
        return;
    }
    display_full_prompt(current_path);
    my_free(current_path);
}
void shell_loop(void)
{
    char *input;
    int should_exit = 0;

    print_welcome_message();

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
