#include "my/my.h"

/**
 * @brief Copy size bytes between two buffers, handling overlap.
 * @param dest: destination buffer.
 * @param src: source buffer.
 * @param size: number of bytes to copy.
 * @return Pointer to dest.
 */
void *my_memmove(void *dest, const void *src, size_t size)
{
    char *d = dest;
    const char *s = src;

    if (d <= s || d >= s + size) {
        my_memcpy(dest, src, size);
        return dest;
    }
    for (size_t i = size; i > 0; i--)
        d[i - 1] = s[i - 1];
    return dest;
}
