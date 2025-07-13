/**
 * ============================================================================
 *                              COLOR DISPLAY IMPLEMENTATION
 * ============================================================================
 * File: color_display.c
 * Description: Display functions for welcome messages and banners.
 * Dependencies: colors.h
 * ============================================================================
 */

#include "../../include/colors.h"

void display_title_banner(void)
{
    my_printf("\n");
    my_printf("%s%s═══════════════════════════════════════════════════════════════════════════════%s\n",
              BRIGHT_CYAN, BOLD, RESET);
    my_printf("%s%s                              %s%s %sPONGSH%s                        %s\n",
              BRIGHT_CYAN, BOLD, BRIGHT_MAGENTA, TERMINAL, BOLD, RESET, RESET);
    my_printf("%s%s═══════════════════════════════════════════════════════════════════════════════%s\n",
              BRIGHT_CYAN, BOLD, RESET);
    my_printf("\n");
}

void display_user_welcome(void)
{
    char *username;
    char *hostname;

    username = get_current_user();
    hostname = get_hostname();
    my_printf("%s%s %sWelcome back, %s%s%s%s!%s Running on %s%s%s%s %s%s%s\n",
              SUCCESS_COLOR, STAR, RESET,
              PROMPT_USER, BOLD, username, RESET, RESET,
              PROMPT_HOST, BOLD, hostname, RESET,
              SUCCESS_COLOR, STAR, RESET);
}

void display_command_help(void)
{
    my_printf("\n");
    my_printf("%s%s %s Type commands to get started, or 'exit' to quit%s\n",
              INFO_COLOR, ARROW_RIGHT, RESET, RESET);
    my_printf("%s%s %sAvailable commands: ls, cd, pwd, echo, cat, clear, exit%s\n",
              INFO_COLOR, LIGHTNING, RESET, RESET);
    my_printf("\n");
}
