#include "my.h"

static void put_unsigned(unsigned int nb)
{
    if (nb >= 10)
        put_unsigned(nb / 10);
    my_putchar('0' + nb % 10);
}

int my_put_nbr(int nb)
{
    unsigned int magnitude = nb;

    if (nb < 0) {
        my_putchar('-');
        magnitude = 0u - magnitude;
    }
    put_unsigned(magnitude);
    return 0;
}
