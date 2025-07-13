/**
 * ===================================================================
 *                              MY_CAT HEADER
 * ===================================================================
 * File: my_cat.h
 * Description: Header file for the my_cat implementation with basic
 *              functionality similar to Unix cat command.
 * Dependencies: pongsh.h
 * ===================================================================
 */

#ifndef MY_CAT_H
    #define MY_CAT_H

    #ifndef _POSIX_C_SOURCE
    #define _POSIX_C_SOURCE 200112L
    #endif

    #include <fcntl.h>
    #include <unistd.h>
    #include <sys/stat.h>
    #include <errno.h>
    #include "pongsh.h"

    #define CAT_BUFFER_SIZE 4096

    int my_cat(const char *filename);
    int cat_file(const char *filename);
    int cat_stdin(void);
    int validate_file(const char *filename);
    void print_cat_error(const char *filename, const char *error_msg);
    int open_file_for_reading(const char *filename);
    int read_and_output_file(int fd, const char *filename);

#endif /* MY_CAT_H */
