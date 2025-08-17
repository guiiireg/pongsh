// ============================
//        MY_PUT_NBR
// ============================
// Made by Guireg on 17/08/2025
// Last update: 17/08/2025
// ============================
#include "../../include/my.h"

int my_put_nbr(int nb)
{
    if (nb < 0) {
        if (nb == -2147483648) {
            my_putchar('-');
            my_putchar('2');
            nb = 147483648;
        } else {
            my_putchar('-');
            nb = -nb;
        }
    }
    if (nb >= 10) {
        my_put_nbr(nb / 10);
    }
    my_putchar(nb % 10 + '0');
    return 0;
}
