#include <stddef.h>

#include "my.h"

/**
 * @brief Zeroes a memory area.
 *
 * @param s The memory area to zero.
 * @param n The number of bytes to zero.
 *
 * @return 0 on success, or -1 on failure.
 */
int my_bzero(void *s, int n)
{
    if (my_memset(s, 0, n) == NULL) {
        return (-1);
    }
    return (0);
}
