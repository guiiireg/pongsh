#include "my.h"

int my_str_isupper(char const *str)
{
    for (; *str; str++)
        if (*str < 'A' || *str > 'Z')
            return 0;
    return 1;
}
