#include <stdlib.h>

#include "my.h"

/**
** @brief Duplicates a string into a newly allocated one.
**
** @param str The string to duplicate.
**
** @return A newly allocated copy of the string, or NULL on failure.
*/
char *my_strdup(char const *str)
{
    char *copy;
    int i = 0;

    if (str == NULL) {
        return (NULL);
    }
    copy = malloc(sizeof(char) * (my_strlen(str) + 1));
    if (copy == NULL) {
        return (NULL);
    }
    while (str[i] != '\0') {
        copy[i] = str[i];
        i += 1;
    }
    copy[i] = '\0';
    return (copy);
}
