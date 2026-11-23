#include "my.h"
#include <limits.h>

static int read_sign(char const **str)
{
    int sign = 1;

    while (**str == '+' || **str == '-') {
        if (**str == '-')
            sign = -sign;
        (*str)++;
    }
    return sign;
}

int my_getnbr(char const *str)
{
    int sign = read_sign(&str);
    int value = 0;
    int limit = -INT_MAX;
    int digit;

    if (sign < 0)
        limit = INT_MIN;
    while (*str >= '0' && *str <= '9') {
        digit = *str - '0';
        if (value < (limit + digit) / 10)
            return 0;
        value = value * 10 - digit;
        str++;
    }
    if (sign < 0)
        return value;
    return -value;
}
