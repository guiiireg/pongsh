#include "my.h"

int my_putstr(char const *str)
{
    for (; *str; str++)
        my_putchar(*str);
    return 0;
}
