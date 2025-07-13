/**
 * ============================================================================
 *                              MY_CD HEADER
 * ============================================================================
 * File: my_cd.h
 * Description: Header file for the my_cd implementation - builtin cd command
 *              for the PONGSH shell.
 * Dependencies: pongsh.h
 * ============================================================================
 */

#ifndef MY_CD_H
    #define MY_CD_H

    #ifndef _POSIX_C_SOURCE
    #define _POSIX_C_SOURCE 200112L
    #endif

    #include <unistd.h>
    #include <sys/stat.h>
    #include <limits.h>
    #include <stdlib.h>
    #include "pongsh.h"

    #ifndef PATH_MAX
        #define PATH_MAX 4096
    #endif

// ---- Function prototypes ----
int my_cd(const char *path);
int validate_directory(const char *path);
char *resolve_cd_path(const char *path);
char *get_current_directory(void);
void update_pwd_env(const char *new_path);
int change_to_directory(const char *path);

#endif /* MY_CD_H */
