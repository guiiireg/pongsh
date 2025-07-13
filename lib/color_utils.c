/**
 * ============================================================================
 *                              COLOR UTILS IMPLEMENTATION
 * ============================================================================
 * File: color_utils.c
 * Description: Implementation of color utility functions for shell display.
 * Dependencies: colors.h, unistd.h, pwd.h
 * ============================================================================
 */
#include "../include/colors.h"
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <stdlib.h>

void print_welcome_message(void)
{
    display_title_banner();
    display_user_welcome();
    display_command_help();
}

char *get_current_user(void)
{
    struct passwd *pw;

    pw = getpwuid(getuid());
    if (pw && pw->pw_name)
        return pw->pw_name;
    return "user";
}

char *get_hostname(void)
{
    static char hostname[256];

    if (gethostname(hostname, sizeof(hostname)) == 0)
        return hostname;
    return "localhost";
}
