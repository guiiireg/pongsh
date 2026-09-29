#include "../../include/my.h"

/**
 * Displays a string on the standard output.
 */
int my_putstr(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        my_putchar(str[i]);
    }
    return 0;
}
