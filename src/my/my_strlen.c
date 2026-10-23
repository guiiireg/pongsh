#include "my/my.h"

/**
 * @brief Compute the length of a null-terminated string.
 * @param str: string to measure.
 * @return Number of characters before the null byte.
 */
int my_strlen(const char *str)
{
    int len = 0;

    while (str[len] != '\0')
        len++;
    return len;
}
