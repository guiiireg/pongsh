#include <stddef.h>

/**
** @brief Copies a memory area to a non-overlapping destination.
**
** The behavior is undefined if the areas overlap.
**
** @param dest The destination memory area.
** @param src The source memory area.
** @param n The number of bytes to copy.
**
** @return A pointer to the destination, or NULL on failure.
*/
void *my_memcpy(void *dest, void const *src, int n)
{
    int i = 0;
    char *dst_bytes = dest;
    char const *src_bytes = src;

    if (dest == NULL || src == NULL || n < 0) {
        return (NULL);
    }
    while (i < n) {
        dst_bytes[i] = src_bytes[i];
        i += 1;
    }
    return (dest);
}
