#include "my/my.h"

static void print_digits(long long value)
{
    if (value < 10) {
        my_putchar('0' + value);
        return;
    }
    print_digits(value / 10);
    my_putchar('0' + value % 10);
}

/**
 * @brief Write a signed decimal number to stdout.
 * @param nb: number to write.
 * @return 0 on success.
 */
int my_put_nbr(int nb)
{
    long long value = nb;

    if (value < 0) {
        my_putchar('-');
        value = -value;
    }
    print_digits(value);
    return 0;
}
