#include "../../include/my.h"

/**
 * @brief Copy a null-terminated string into a buffer.
 * @param dest: destination buffer, must be large enough.
 * @param src: string to copy.
 * @return Pointer to dest.
 */
char *my_strcpy(char *dest, const char *src)
{
    int i = 0;

    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}
