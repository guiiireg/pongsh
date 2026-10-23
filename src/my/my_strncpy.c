#include "../../include/my.h"

/**
 * @brief Copy at most n characters of a string into a buffer.
 * @param dest: destination buffer, must hold at least n characters.
 * @param src: string to copy.
 * @param n: maximum number of characters to copy.
 * @return Pointer to dest.
 */
char *my_strncpy(char *dest, const char *src, int n)
{
    int i = 0;

    while (i < n && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    for (; i < n; i++)
        dest[i] = '\0';
    return dest;
}
