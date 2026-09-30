/**
 * Recursively computes nb raised to the power of a power.
 * Returns 0 if a power is negative.
 */
int my_compute_power_rec(int nb, int power) {
  if (power < 0)
    return 0;
  if (power == 0)
    return 1;
  return (nb * my_compute_power_rec(nb, power - 1));
}
