#include "../../include/my.h"

/**
 * @brief Compare two memory areas byte by byte.
 * @param s1: first buffer.
 * @param s2: second buffer.
 * @param size: number of bytes to compare.
 * @return Difference between the first differing bytes.
 */
int my_memcmp(const void *s1, const void *s2, size_t size)
{
    const char *a = s1;
    const char *b = s2;

    for (size_t i = 0; i < size; i++) {
        if (a[i] != b[i])
            return a[i] - b[i];
    }
    return 0;
}
