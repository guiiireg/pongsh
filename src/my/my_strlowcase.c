#include "my/my.h"

/**
 * @brief Lowercase every letter of a string in place.
 * @param str: string to modify.
 * @return Pointer to str.
 */
char *my_strlowcase(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 32;
    }
    return str;
}
