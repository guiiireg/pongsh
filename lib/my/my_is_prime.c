#include "my.h"

int my_is_prime(int nb)
{
    if (nb <= 2)
        return nb == 2;
    if (nb % 2 == 0)
        return 0;
    for (int divisor = 3; divisor <= nb / divisor; divisor += 2)
        if (nb % divisor == 0)
            return 0;
    return 1;
}
