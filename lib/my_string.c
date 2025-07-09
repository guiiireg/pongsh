/**
 * ============================================================================
 *                           STRING MANIPULATION LIBRARY
 * ============================================================================
 * File: my_string.c
 * Description: This file contains essential string manipulation functions
 *              including duplication, comparison, copying, and concatenation.
 * Dependencies: pongsh.h
 * ============================================================================
 */

#include "../include/pongsh.h"

char *my_strdup(const char *str)
{
    char *dup;
    int len = my_strlen(str);
    int i = 0;

    dup = my_malloc(len + 1);
    if (!dup)
        return NULL;
    while (i < len) {
        dup[i] = str[i];
        i++;
    }
    dup[i] = '\0';
    return dup;
}

int my_strcmp(const char *s1, const char *s2)
{
    int i = 0;

    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return s1[i] - s2[i];
}

char *my_strcpy(char *dest, const char *src)
{
    int i = 0;

    while (src[i]) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

char *my_strcat(char *dest, const char *src)
{
    int dest_len = my_strlen(dest);
    int i = 0;

    while (src[i]) {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[dest_len + i] = '\0';
    return dest;
}
