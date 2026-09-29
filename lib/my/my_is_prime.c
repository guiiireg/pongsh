/**
 * Checks whether nb is a prime number.
 * Returns 1 if nb is prime, otherwise returns 0.
 */ 
int my_is_prime(int nb)
{
    int i;

    if (nb <= 1)
        return 0;
    if (nb == 2)
        return 1;
    if (nb % 2 == 0)
        return 0;
    i = 3;
    while (i <= nb / i) {
        if (nb % i == 0)
            return 0;
        i += 2;
    }
    return 1;
}
