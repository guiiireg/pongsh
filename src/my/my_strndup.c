#include "my/my.h"
#include <stdlib.h>

/**
 * @brief Duplicate at most n characters of a string into a new allocation.
 * @param src: string to duplicate.
 * @param n: maximum number of characters to copy.
 * @return Pointer to the new null-terminated string, NULL on failure.
 */
char *my_strndup(const char *src, int n)
{
    int len = my_strlen(src);
    char *copy = NULL;

    if (len > n)
        len = n;
    copy = malloc(sizeof(char) * (len + 1));
    if (copy == NULL)
        return NULL;
    my_strncpy(copy, src, len);
    copy[len] = '\0';
    return copy;
}
