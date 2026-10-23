#include "../../include/my.h"

/**
 * @brief Fill a memory area with a byte value.
 * @param ptr: buffer to fill.
 * @param c: byte value to write.
 * @param size: number of bytes to fill.
 * @return Pointer to ptr.
 */
void *my_memset(void *ptr, int c, size_t size)
{
    char *p = ptr;

    for (size_t i = 0; i < size; i++)
        p[i] = (char)c;
    return ptr;
}
