/**
 * ============================================================================
 *                              PROJECT HEADER
 * ============================================================================
 * File: pongsh.h
 * Description: Main header file for the PONGSH project containing function
 *              prototypes, constants, and structure definitions.
 * Dependencies: stdio.h, stdlib.h, string.h, unistd.h
 * ============================================================================
 */

#ifndef PONGSH_H
    #define PONGSH_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>

    #define BUFFER_SIZE 1024
    #define MAX_PATH 256

typedef struct s_data {
    char *buffer;
    int size;
    int capacity;
} data_t;

// ---- Shell main loop ----
void shell_loop(void);

// ---- Input handling ----
char *read_input(void);

// ---- Command execution ----
int execute_command(const char *command);

// ---- Basic I/O functions ----
void my_putchar(char c);
int my_putstr(const char *str);
int my_putnbr(int nb);
int my_strlen(const char *str);

// ---- String manipulation functions ----
char *my_strdup(const char *str);
int my_strcmp(const char *s1, const char *s2);
char *my_strcpy(char *dest, const char *src);
char *my_strcat(char *dest, const char *src);

// ---- Memory management functions ----
void *my_malloc(size_t size);
void my_free(void *ptr);
void *my_memset(void *ptr, int value, size_t num);

// ---- Utility functions ----
int my_atoi(const char *str);
char *my_itoa(int value);

    #include "my_printf.h"
    #include "my_ls.h"
    #include "my_cd.h"

#endif /* PONGSH_H */
