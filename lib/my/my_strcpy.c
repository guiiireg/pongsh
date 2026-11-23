#include "my.h"

char *my_strcpy(char *dest, char const *src)
{
    char *start = dest;

    while (*src) {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return start;
}
