#include "my.h"
#include <limits.h>

int my_getnbr(char const *str)
{
    int sign = 1;
    int value = 0;
    int limit;
    int digit;

    for (; *str == '+' || *str == '-'; str++)
        if (*str == '-')
            sign = -sign;
    limit = sign < 0 ? INT_MIN : -INT_MAX;
    for (; *str >= '0' && *str <= '9'; str++) {
        digit = *str - '0';
        if (value < (limit + digit) / 10)
            return 0;
        value = value * 10 - digit;
    }
    return sign < 0 ? value : -value;
}
