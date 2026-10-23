#include "my/my.h"

/**
 * @brief Uppercase every letter of a string in place.
 * @param str: string to modify.
 * @return Pointer to str.
 */
char *my_strupcase(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] -= 32;
    }
    return str;
}
