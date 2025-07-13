/**
 * ============================================================================
 *                              COLOR PRINT IMPLEMENTATION
 * ============================================================================
 * File: color_print.c
 * Description: Implementation of color printing functions for shell display.
 * Dependencies: colors.h
 * ============================================================================
 */

#include "../include/colors.h"

void print_colored(const char *color, const char *text)
{
    my_printf("%s%s%s", color, text, RESET);
}

void print_success(const char *message)
{
    my_printf("%s%s%s %s%s\n", SUCCESS_COLOR, CHECK_MARK, RESET,
              SUCCESS_COLOR, message ? message : "Success");
    my_printf("%s", RESET);
}

void print_error(const char *message)
{
    my_printf("%s%s%s %s%s\n", ERROR_COLOR, CROSS_MARK, RESET,
              ERROR_COLOR, message ? message : "Error");
    my_printf("%s", RESET);
}

void print_warning(const char *message)
{
    my_printf("%s%s%s %s%s\n", WARNING_COLOR, WARNING, RESET,
              WARNING_COLOR, message ? message : "Warning");
    my_printf("%s", RESET);
}

void print_info(const char *message)
{
    my_printf("%s%s%s %s%s\n", INFO_COLOR, INFO, RESET,
              INFO_COLOR, message ? message : "Info");
    my_printf("%s", RESET);
}
