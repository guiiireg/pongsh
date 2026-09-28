#include "../../include/my.h"

int my_put_nbr(int nb)
{
    long nbr = nb;

    if (nbr < 0) {
        my_putchar('-');
        nbr = -nbr;
    }
    if (nbr >= 10) {
        my_put_nbr(nbr / 10);
    }
    my_putchar((nbr % 10) + '0');
    return 0;
}
