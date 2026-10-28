#include <stddef.h>

#include "my.h"

/**
 * @brief Appends at most n characters of a string to another.
 *
 * The destination is always null-terminated.
 *
 * @param dest The destination string, with enough space to hold both.
 * @param src The string to append.
 * @param n The maximum number of characters to append.
 *
 * @return A pointer to the destination string, or NULL on failure.
 */
char *my_strncat(char *dest, char const *src, int n)
{
    int i = 0;
    int len;

    if (dest == NULL || src == NULL || n < 0) {
        return (NULL);
    }
    len = my_strlen(dest);
    if (len == -1) {
        return (NULL);
    }
    while (i < n && src[i] != '\0') {
        dest[len + i] = src[i];
        i += 1;
    }
    dest[len + i] = '\0';
    return (dest);
}
