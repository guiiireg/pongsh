#include <stddef.h>

/**
 * @brief Copies a memory area, handling overlapping areas safely.
 *
 * Unlike my_memcpy, the copy is done backward when the destination
 * overlaps the source, so no byte is overwritten before being read.
 *
 * @param dest The destination memory area.
 * @param src The source memory area.
 * @param n The number of bytes to copy.
 *
 * @return A pointer to the destination, or NULL on failure.
 */
void *my_memmove(void *dest, void const *src, int n)
{
    int i = 0;
    char *dst_bytes = dest;
    char const *src_bytes = src;

    if (dest == NULL || src == NULL || n < 0) {
        return (NULL);
    }
    if (dest < src) {
        while (i < n) {
            dst_bytes[i] = src_bytes[i];
            i += 1;
        }
        return (dest);
    }
    i = n - 1;
    while (i >= 0) {
        dst_bytes[i] = src_bytes[i];
        i -= 1;
    }
    return (dest);
}
