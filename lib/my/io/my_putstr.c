#include <unistd.h>

#include "my.h"

/**
 * @brief Writes a string to the standard output.
 *
 * The string is written with a single write call.
 *
 * @param str The string to write.
 *
 * @return The number of bytes written, or -1 on failure.
 */
int my_putstr(char const *str)
{
    int len;

    if (str == NULL) {
        return (-1);
    }
    len = my_strlen(str);
    if (write(STDOUT_FILENO, str, len) != len) {
        return (-1);
    }
    return (len);
}
