#include "../../include/my.h"

/**
 * Returns the first prime number greater than or equal to nb.
 * Returns 0 if no prime can be found within the integer range.
 */
int my_find_prime_sup(int nb)
{
    if (nb <= 2)
        return 2;
    while (!my_is_prime(nb)) {
        if (nb == 2147483647)
            return 0;
        nb++;
    }
    return nb;
}
