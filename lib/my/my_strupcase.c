#include "my.h"

char *my_strupcase(char *str)
{
    for (char *current = str; *current; current++)
        if (*current >= 'a' && *current <= 'z')
            *current = *current - ('a' - 'A');
    return str;
}
