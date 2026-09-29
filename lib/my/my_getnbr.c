#include "../../include/my.h"

int my_getnbr(const char *str)
{
    int i = 0;
    int sign = 1;
    long nb = 0;

    if (str == 0)
        return 0;
    while (str[i] == '+' || str[i] == '-') {
        if (str[i] == '-')
            sign *= -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9') {
        nb = nb * 10 + (str[i] - '0');
        if (nb > 2147483648L || (sign == 1 && nb > 2147483647))
            return 0;
        i++;
    }
    return (int)(nb * sign);
}
