#include <unistd.h>

/**
 * Displays a character on the standard outpout.
 */
void my_putchar(char c) { write(1, &c, 1); }
