#include <unistd.h>

/**
 * @brief Writes a string to the standard error output.
 *
 * @param str The string to write.
 *
 * @return The number of bytes written, or -1 on failure.
 */
int my_puterr(char const *str)
{
    int count = 0;

    if (str == NULL) {
        return (-1);
    }
    while (str[count] != '\0') {
        if (write(STDERR_FILENO, &str[count], 1) == -1) {
            return (-1);
        }
        count += 1;
    }
    return (count);
}
