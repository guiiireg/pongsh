#include "my.h"

char *my_strncat(char *dest, char const *src, int nb)
{
    char *end = dest + my_strlen(dest);

    for (int index = 0; index < nb && src[index]; index++)
        *end++ = src[index];
    *end = '\0';
    return dest;
}
