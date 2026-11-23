#include "my.h"
#include <limits.h>

int my_find_prime_sup(int nb)
{
    if (nb <= 2)
        return 2;
    if (nb % 2 == 0)
        nb++;
    while (!my_is_prime(nb)) {
        if (nb > INT_MAX - 2)
            return 0;
        nb += 2;
    }
    return nb;
}
