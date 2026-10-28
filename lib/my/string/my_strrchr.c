#include <stddef.h>

#include "my.h"

/**
** @brief Finds the last occurrence of a character in a string.
**
** @param str The string to search in.
** @param c The character to find.
**
** @return A pointer to the last occurrence, to the terminating null
**         byte if c is '\0', or NULL if not found.
*/
char *my_strrchr(char const *str, int c)
{
    int len;

    if (str == NULL) {
        return (NULL);
    }
    len = my_strlen(str);
    while (len >= 0) {
        if (str[len] == c) {
            return ((char *)&str[len]);
        }
        len -= 1;
    }
    return (NULL);
}
