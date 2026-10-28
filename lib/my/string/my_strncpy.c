#include <stddef.h>

/**
** @brief Copies at most n characters of a string into another.
**
** If src is shorter than n, the destination is padded with null bytes.
**
** @param dest The destination buffer.
** @param src The string to copy.
** @param n The maximum number of characters to copy.
**
** @return A pointer to the destination string, or NULL on failure.
*/
char *my_strncpy(char *dest, char const *src, int n)
{
    int i = 0;

    if (dest == NULL || src == NULL || n < 0) {
        return (NULL);
    }
    while (i < n && src[i] != '\0') {
        dest[i] = src[i];
        i += 1;
    }
    while (i < n) {
        dest[i] = '\0';
        i += 1;
    }
    return (dest);
}
