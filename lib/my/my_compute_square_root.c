#include "my.h"

int my_compute_square_root(int nb)
{
    int first = 1;
    int last = nb / 2;
    int middle;

    if (nb == 1)
        return 1;
    while (first <= last) {
        middle = first + (last - first) / 2;
        if (middle == nb / middle && nb % middle == 0)
            return middle;
        if (middle <= nb / middle)
            first = middle + 1;
        else
            last = middle - 1;
    }
    return 0;
}
