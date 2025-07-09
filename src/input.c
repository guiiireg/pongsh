/**
 * =======================================================================
 *                              PONGSH - INPUT
 * =======================================================================
 * File: input.c
 * Description: Input handling for the PONGSH shell.
 * Dependencies: pongsh.h
 * =======================================================================
 */
#include "../include/pongsh.h"

static int read_first_char(char *c)
{
    ssize_t bytes_read = read(0, c, 1);

    if (bytes_read <= 0)
        return -1;
    return 0;
}

static int read_line_loop(char *buffer, int *i, char first_c)
{
    char c = first_c;
    ssize_t bytes_read;

    while (c != '\n' && *i < BUFFER_SIZE - 1) {
        buffer[*i] = c;
        (*i)++;
        bytes_read = read(0, &c, 1);
        if (bytes_read <= 0)
            break;
    }
    buffer[*i] = '\0';
    return 0;
}

char *read_input(void)
{
    char *buffer = my_malloc(BUFFER_SIZE);
    int i = 0;
    char c;

    if (!buffer)
        return NULL;
    if (read_first_char(&c) == -1) {
        my_free(buffer);
        return NULL;
    }
    read_line_loop(buffer, &i, c);
    return buffer;
}
