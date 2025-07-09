/**
 * =======================================================================
 *                              PONGSH - SHELL
 * =======================================================================
 * File: main.c
 * Description: Main entry point for the PONGSH shell. Implements the main
 *              command loop and basic shell functionality.
 * Dependencies: pongsh.h
 * =======================================================================
 */

#include "../include/pongsh.h"

/**
 * @brief Reads a line of input from stdin
 * @return Pointer to the input string (must be freed)
 */
char *read_input(void)
{
    char *buffer = my_malloc(BUFFER_SIZE);
    int i = 0;
    char c;
    ssize_t bytes_read;

    if (!buffer)
        return NULL;
    bytes_read = read(0, &c, 1);
    if (bytes_read <= 0) {
        my_free(buffer);
        return NULL;
    }
    while (c != '\n' && i < BUFFER_SIZE - 1) {
        buffer[i] = c;
        i++;
        bytes_read = read(0, &c, 1);
        if (bytes_read <= 0) {
            break;
        }
    }
    buffer[i] = '\0';
    return buffer;
}

/**
 * @brief Handle ls command arguments
 * @param args The arguments string
 */
static void handle_ls_args(const char *args)
{
    if (args[0] == '-') {
        my_ls_with_flags(NULL, args + 1);
    } else {
        my_ls(args);
    }
}

/**
 * @brief Handle ls commands with arguments
 * @param command The command string
 * @return 0 to continue
 */
static int handle_ls_command(const char *command)
{
    if (my_strcmp(command, "ls") == 0) {
        my_ls(NULL);
        return 0;
    }
    if (my_strlen(command) >= 2 && command[0] == 'l' && command[1] == 's') {
        if (my_strlen(command) == 2) {
            my_ls(NULL);
            return 0;
        }
        if (command[2] == ' ') {
            handle_ls_args(command + 3);
            return 0;
        }
        return 0;
    }
    return -1;
}

/**
 * @brief Processes and executes a command
 * @param command The command to execute
 * @return 0 to continue, 1 to exit
 */
int execute_command(const char *command)
{
    if (my_strcmp(command, "exit") == 0) {
        return 1;
    }
    if (my_strcmp(command, "clear") == 0) {
        system("clear");
        return 0;
    }
    if (handle_ls_command(command) == 0) {
        return 0;
    }
    if (my_strlen(command) == 0) {
        return 0;
    }
    my_printf("pongsh: command not found: %s\n", command);
    return 0;
}

/**
 * @brief Main shell loop
 */
void shell_loop(void)
{
    char *input;
    int should_exit = 0;

    while (!should_exit) {
        my_printf("pongsh$ ");
        input = read_input();
        if (!input) {
            my_printf("Error: Failed to read input\n");
            continue;
        }
        should_exit = execute_command(input);
        my_free(input);
    }
}

/**
 * @brief Main entry point of the shell
 * @return Exit status
 */
int main(void)
{
    shell_loop();
    return 0;
}
