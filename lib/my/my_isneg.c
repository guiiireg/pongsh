#include "../../include/my.h"

/**
 * Displays 'N' if the number is negative, otherwise displays 'P'.
 */
int my_isneg(int nb) {
  if (nb < 0) {
    my_putchar('N');
  } else {
    my_putchar('P');
  }
  return 0;
}
