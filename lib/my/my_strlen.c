#include "my.h"

int my_strlen(char const *str)
{
    int length = 0;

    while (str[length])
        length++;
    return length;
}
