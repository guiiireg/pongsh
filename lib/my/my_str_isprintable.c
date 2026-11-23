#include "my.h"

int my_str_isprintable(char const *str)
{
    for (; *str; str++)
        if ((unsigned char)*str < 32 || (unsigned char)*str > 126)
            return 0;
    return 1;
}
