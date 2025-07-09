/**
 * =======================================================================
 *                              PONGSH - SHELL LOOP
 * =======================================================================
 * File: shell.c
 * Description: Main shell loop for the PONGSH shell.
 * Dependencies: pongsh.h
 * =======================================================================
 */
#include "../include/pongsh.h"

void shell_loop(void)
{
    char *input;
    int should_exit = 0;

    while (!should_exit) {
        my_printf("pongsh$ ");
        input = read_input();
        if (!input) {
            break;
        }
        should_exit = execute_command(input);
        my_free(input);
    }
}
