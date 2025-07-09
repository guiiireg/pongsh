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

/**
 * @brief Creates a duplicate of a string
 * @param str The string to duplicate
 * @return A pointer to the new string, or NULL on failure
 */
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

/**
 * @brief Compares two strings lexicographically
 * @param s1 First string
 * @param s2 Second string
 * @return 0 if equal, negative if s1 < s2, positive if s1 > s2
 */
int my_strcmp(const char *s1, const char *s2)
{
    int i = 0;

    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return s1[i] - s2[i];
}

/**
 * @brief Copies a string to another buffer
 * @param dest Destination buffer
 * @param src Source string
 * @return Pointer to destination buffer
 */
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

/**
 * @brief Concatenates two strings
 * @param dest Destination buffer (must have enough space)
 * @param src Source string to append
 * @return Pointer to destination buffer
 */
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
