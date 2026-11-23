#include "my.h"
#include <limits.h>
#include <stdint.h>

static int checked_product(int a, int b)
{
    int64_t product = (int64_t)a * b;

    if (product < INT_MIN || product > INT_MAX)
        return 0;
    return (int)product;
}

int my_compute_power_rec(int nb, int power)
{
    int half;
    int result;

    if (power < 0)
        return 0;
    if (power == 0)
        return 1;
    if (power == 1)
        return nb;
    half = my_compute_power_rec(nb, power / 2);
    result = checked_product(half, half);
    if (power % 2)
        return checked_product(result, nb);
    return result;
}
