#include <stddef.h>

/**
 * @brief Copies a string into another.
 *
 * @param dest The destination buffer.
 * @param src The string to copy.
 *
 * @return A pointer to the destination string, or NULL on failure.
 */
char *my_strcpy(char *dest, char const *src)
{
    int i = 0;

    if (dest == NULL || src == NULL) {
        return (NULL);
    }
    while (src[i] != '\0') {
        dest[i] = src[i];
        i += 1;
    }
    dest[i] = '\0';
    return (dest);
}
