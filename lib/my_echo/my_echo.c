/**
 * ===================================================================
 *                              MY_ECHO CORE
 * ===================================================================
 * File: my_echo.c
 * Description: Core implementation of my_echo builtin command that
 *              displays the arguments passed to it.
 * Dependencies: my_echo.h
 * ===================================================================
 */

#include "../../include/my_echo.h"

int my_echo(const char *args)
{
    if (!args || my_strlen(args) == 0) {
        my_printf("\n");
        return 0;
    }
    my_printf("%s\n", args);
    return 0;
}
