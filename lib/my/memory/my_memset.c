#include <stddef.h>

/**
** @brief Fills a memory area with a byte value.
**
** @param s The memory area to fill.
** @param c The byte value, converted to an unsigned char.
** @param n The number of bytes to fill.
**
** @return A pointer to the memory area, or NULL on failure.
*/
void *my_memset(void *s, int c, int n)
{
    int i = 0;
    char *bytes = s;

    if (s == NULL || n < 0) {
        return (NULL);
    }
    while (i < n) {
        bytes[i] = (unsigned char)c;
        i += 1;
    }
    return (s);
}
