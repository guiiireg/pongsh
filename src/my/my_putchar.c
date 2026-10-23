#include "my/my.h"
#include <unistd.h>

/**
 * @brief Write a single character to stdout.
 * @param c: character to write.
 */
void my_putchar(char c)
{
    write(1, &c, 1);
}
