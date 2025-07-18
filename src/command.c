/**
 * =======================================================================
 *                              PONGSH - COMMAND
 * =======================================================================
 * File: command.c
 * Description: Command execution and ls handling for the PONGSH shell.
 * Dependencies: pongsh.h
 * =======================================================================
 */
#include "../include/pongsh.h"

static void handle_ls_args(const char *args)
{
    if (args[0] == '-') {
        my_ls_with_flags(NULL, args + 1);
    } else {
        my_ls(args);
    }
}

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

static int handle_cd_command(const char *command)
{
    if (my_strcmp(command, "cd") == 0) {
        my_cd(NULL);
        return 0;
    }
    if (my_strlen(command) >= 2 && command[0] == 'c' && command[1] == 'd') {
        if (my_strlen(command) == 2) {
            my_cd(NULL);
            return 0;
        }
        if (command[2] == ' ') {
            my_cd(command + 3);
            return 0;
        }
        return 0;
    }
    return -1;
}

static int handle_pwd_command(const char *command)
{
    if (my_strcmp(command, "pwd") == 0) {
        my_pwd();
        return 0;
    }
    return -1;
}

static int handle_echo_command(const char *command)
{
    if (my_strcmp(command, "echo") == 0) {
        my_echo(NULL);
        return 0;
    }
    if (my_strlen(command) >= 4 && command[0] == 'e' && command[1] == 'c' &&
        command[2] == 'h' && command[3] == 'o') {
        if (my_strlen(command) == 4) {
            my_echo(NULL);
            return 0;
        }
        if (command[4] == ' ') {
            my_echo(command + 5);
            return 0;
        }
        return 0;
    }
    return -1;
}

static int handle_cat_command(const char *command)
{
    if (my_strcmp(command, "cat") == 0) {
        my_cat(NULL);
        return 0;
    }
    if (my_strlen(command) >= 3 && command[0] == 'c' && command[1] == 'a' &&
        command[2] == 't') {
        if (my_strlen(command) == 3) {
            my_cat(NULL);
            return 0;
        }
        if (command[3] == ' ') {
            my_cat(command + 4);
            return 0;
        }
        return 0;
    }
    return -1;
}

int execute_command(const char *command)
{
    if (my_strcmp(command, "exit") == 0) {
                my_printf("\n%s%s %sGoodbye! Thanks for using %s%sPONGSH%s %s%s%s\n",
                  SUCCESS_COLOR, HEART, RESET,
                  BRIGHT_MAGENTA, BOLD, RESET,
                  SUCCESS_COLOR, STAR, RESET);
        my_printf("%s%s %sSee you next time! %s%s%s\n\n",
                  INFO_COLOR, ARROW_RIGHT, RESET,
                  INFO_COLOR, LIGHTNING, RESET);
        return 1;
    }
    if (my_strcmp(command, "clear") == 0) {
        system("clear");
                        my_printf("%s%s %sWelcome to %s%sPONGSH%s - A modern shell with cat support %s%s%s\n\n",
                  INFO_COLOR, TERMINAL, RESET,
                  BRIGHT_MAGENTA, BOLD, RESET,
                  SUCCESS_COLOR, STAR, RESET);
        return 0;
    }
    if (handle_ls_command(command) == 0) {
        return 0;
    }
    if (handle_cd_command(command) == 0) {
        return 0;
    }
    if (handle_pwd_command(command) == 0) {
        return 0;
    }
    if (handle_echo_command(command) == 0) {
        return 0;
    }
    if (handle_cat_command(command) == 0) {
        return 0;
    }
    if (my_strlen(command) == 0) {
        return 0;
    }
        my_printf("%s%s %spongsh: command not found: %s%s%s\n",
              ERROR_COLOR, CROSS_MARK, RESET,
              ERROR_COLOR, command, RESET);
    return 0;
}
