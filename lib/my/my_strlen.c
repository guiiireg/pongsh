#include <stddef.h>

/**
** @brief Computes the length of a string.
**
** @param str The string to measure.
**
** @return The number of characters before the terminating null byte,
**         or -1 on failure.
*/
int my_strlen(char const *str)
{
    int len = 0;

    if (str == NULL) {
        return (-1);
    }
    while (str[len] != '\0') {
        len += 1;
    }
    return (len);
}
