#include "my.h"

char *my_revstr(char *str)
{
    int right = my_strlen(str) - 1;
    char tmp;

    for (int left = 0; left < right; left++) {
        tmp = str[left];
        str[left] = str[right];
        str[right] = tmp;
        right--;
    }
    return str;
}
