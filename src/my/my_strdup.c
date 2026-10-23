#include "my/my.h"
#include <stdlib.h>

/**
 * @brief Duplicate a null-terminated string into a new allocation.
 * @param src: string to duplicate.
 * @return Pointer to the new string, NULL on allocation failure.
 */
char *my_strdup(const char *src)
{
    char *copy = malloc(sizeof(char) * (my_strlen(src) + 1));

    if (copy == NULL)
        return NULL;
    my_strcpy(copy, src);
    return copy;
}
