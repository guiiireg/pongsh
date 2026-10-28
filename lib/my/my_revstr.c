#include <stddef.h>

#include "my.h"

/**
** @brief Reverses a string in place.
**
** @param str The string to reverse.
**
** @return The length of the string, or -1 on failure.
*/
int my_revstr(char *str)
{
    int i = 0;
    int j;
    char tmp;

    if (str == NULL) {
        return (-1);
    }
    j = my_strlen(str) - 1;
    while (i < j) {
        tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
        i += 1;
        j -= 1;
    }
    return (my_strlen(str));
}
