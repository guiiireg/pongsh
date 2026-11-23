#include "my.h"

int my_str_isalpha(char const *str)
{
    for (; *str; str++)
        if ((*str < 'a' || *str > 'z') && (*str < 'A' || *str > 'Z'))
            return 0;
    return 1;
}
