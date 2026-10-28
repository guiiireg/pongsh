#include <stddef.h>

/**
 * @brief Finds the first occurrence of a byte value in a memory area.
 *
 * @param s The memory area to search in.
 * @param c The byte value to find, converted to an unsigned char.
 * @param n The number of bytes to search.
 *
 * @return A pointer to the first occurrence, or NULL if not found.
 */
void *my_memchr(void const *s, int c, int n)
{
    int i = 0;
    char const *bytes = s;

    if (s == NULL || n < 0) {
        return (NULL);
    }
    while (i < n) {
        if (bytes[i] == (unsigned char)c) {
            return ((void *)&bytes[i]);
        }
        i += 1;
    }
    return (NULL);
}
