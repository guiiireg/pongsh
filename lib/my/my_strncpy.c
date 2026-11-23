#include "my.h"

char *my_strncpy(char *dest, char const *src, int n)
{
    int index = 0;

    while (index < n && src[index]) {
        dest[index] = src[index];
        index++;
    }
    while (index < n)
        dest[index++] = '\0';
    return dest;
}
