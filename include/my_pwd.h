/**
 * ============================================================================
 *                              MY_PWD HEADER
 * ============================================================================
 * File: my_pwd.h
 * Description: Header file for the my_pwd implementation - builtin pwd command
 *              for the PONGSH shell.
 * Dependencies: pongsh.h
 * ============================================================================
 */

#ifndef MY_PWD_H
    #define MY_PWD_H

    #define _POSIX_C_SOURCE 200112L

    #include <unistd.h>
    #include <limits.h>
    #include <stdlib.h>
    #include "pongsh.h"

    #ifndef PATH_MAX
        #define PATH_MAX 4096
    #endif

// ---- Function prototypes ----
int my_pwd(void);

#endif /* MY_PWD_H */
