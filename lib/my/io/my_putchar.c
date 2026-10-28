#include <unistd.h>

/**
 * @brief Writes a single character to the standard output.
 *
 * @param c The character to write.
 *
 * @return The number of bytes written, or -1 on failure.
 */
int my_putchar(char c)
{
    return (write(STDOUT_FILENO, &c, 1));
}
