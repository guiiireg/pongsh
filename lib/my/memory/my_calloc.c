#include <limits.h>
#include <stddef.h>
#include <stdlib.h>

#include "my.h"

/**
 * @brief Allocates memory for an array and zeroes it.
 *
 * Composes malloc and my_memset. The multiplication is checked
 * against overflow.
 *
 * @param nmemb The number of elements.
 * @param size The size of each element.
 *
 * @return A pointer to the zeroed memory area, or NULL on failure.
 */
void *my_calloc(int nmemb, int size)
{
    int total;
    void *ptr;

    if (nmemb <= 0 || size <= 0) {
        return (NULL);
    }
    if (nmemb > INT_MAX / size) {
        return (NULL);
    }
    total = nmemb * size;
    ptr = malloc(total);
    if (ptr == NULL) {
        return (NULL);
    }
    return (my_memset(ptr, 0, total));
}
