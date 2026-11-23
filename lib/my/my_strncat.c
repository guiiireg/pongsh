#include "my.h"

char *my_strncat(char *dest, char const *src, int nb)
{
    char *end = dest + my_strlen(dest);
    int index = 0;

    while (index < nb && src[index]) {
        end[index] = src[index];
        index++;
    }
    end[index] = '\0';
    return dest;
}
