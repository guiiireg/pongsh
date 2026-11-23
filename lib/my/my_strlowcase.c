#include "my.h"

char *my_strlowcase(char *str)
{
    for (char *current = str; *current; current++)
        if (*current >= 'A' && *current <= 'Z')
            *current = *current + ('a' - 'A');
    return str;
}
