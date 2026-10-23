#include "../../include/my.h"

/**
 * @brief Copy size bytes from a source buffer to a destination buffer.
 * @param dest: destination buffer.
 * @param src: source buffer.
 * @param size: number of bytes to copy.
 * @return Pointer to dest.
 */
void *my_memcpy(void *dest, const void *src, size_t size)
{
    char *d = dest;
    const char *s = src;

    for (size_t i = 0; i < size; i++)
        d[i] = s[i];
    return dest;
}
