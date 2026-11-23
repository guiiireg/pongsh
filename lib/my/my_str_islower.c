#include "my.h"

int my_str_islower(char const *str)
{
    for (; *str; str++)
        if (*str < 'a' || *str > 'z')
            return 0;
    return 1;
}
