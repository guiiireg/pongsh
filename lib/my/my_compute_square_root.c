/**
 * Returns the integer square root of nb if it's a perfect square.
 * Returns 0 if nb has no integer square root.
 */
int my_compute_square_root(int nb)
{
    int i;

    if (nb <= 0)
        return 0;
    if (nb == 1)
        return 1;
    i = 1;
    while (i <= nb / i) {
        if (i * i == nb)
            return i;
        i++;
    }
    return 0;
}
