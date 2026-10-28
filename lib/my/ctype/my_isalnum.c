#include "my.h"

/**
 * @brief Checks whether a character is alphanumeric.
 *
 * @param c The character to check.
 *
 * @return 1 if the character is alphanumeric, 0 otherwise.
 */
int my_isalnum(int c)
{
    if (my_isalpha(c) == 1 || my_isdigit(c) == 1) {
        return (1);
    }
    return (0);
}
