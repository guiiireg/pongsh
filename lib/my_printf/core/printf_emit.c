#include <unistd.h>

#include "my.h"
#include "my_printf_internal.h"

/**
 * @brief Accumulates the status of a writing helper.
 *
 * The -1 error status is absorbing: once a write fails the total
 * stays -1.
 *
 * @param status The status of the last write.
 * @param total The accumulated total.
 *
 * @return The new total, or -1 on failure.
 */
int pf_add_status(int status, int total)
{
    if (status == -1) {
        return (-1);
    }
    return (total + status);
}

/**
 * @brief Writes a character repeatedly.
 *
 * @param c The character to write.
 * @param count The number of times to write it.
 *
 * @return The number of bytes written, or -1 on failure.
 */
int pf_repeat(char c, int count)
{
    int i = 0;
    int total = 0;

    while (i < count) {
        total = pf_add_status(my_putchar(c), total);
        if (total == -1) {
            return (-1);
        }
        i += 1;
    }
    return (total);
}

/**
 * @brief Writes the first len characters of a string.
 *
 * The characters are written with a single write call.
 *
 * @param str The string to write from.
 * @param len The number of characters to write.
 *
 * @return The number of bytes written, or -1 on failure.
 */
int pf_write_chars(char const *str, int len)
{
    if (len < 0) {
        return (0);
    }
    if (write(STDOUT_FILENO, str, len) != len) {
        return (-1);
    }
    return (len);
}
