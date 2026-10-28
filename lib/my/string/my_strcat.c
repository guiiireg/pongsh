#include <stddef.h>

#include "my.h"

/**
 * @brief Appends a string to another.
 *
 * @param dest The destination string, with enough space to hold both.
 * @param src The string to append.
 *
 * @return A pointer to the destination string, or NULL on failure.
 */
char *my_strcat(char *dest, char const *src)
{
    int i = 0;
    int len;

    if (dest == NULL || src == NULL) {
        return (NULL);
    }
    len = my_strlen(dest);
    if (len == -1) {
        return (NULL);
    }
    while (src[i] != '\0') {
        dest[len + i] = src[i];
        i += 1;
    }
    dest[len + i] = '\0';
    return (dest);
}
