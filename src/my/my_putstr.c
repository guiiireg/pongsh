#include "../../include/my.h"
#include <unistd.h>

/**
 * @brief Write a null-terminated string to stdout.
 * @param str: string to write.
 * @return Number of characters written.
 */
int my_putstr(const char *str)
{
    return write(1, str, my_strlen(str));
}
