#include "my/my.h"

/**
 * @brief Append at most n characters of a string to another.
 * @param dest: destination buffer, must hold the result plus a null byte.
 * @param src: string to append.
 * @param n: maximum number of characters to append.
 * @return Pointer to dest.
 */
char *my_strncat(char *dest, const char *src, int n)
{
    int dest_len = my_strlen(dest);
    int i = 0;

    while (i < n && src[i] != '\0') {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[dest_len + i] = '\0';
    return dest;
}
