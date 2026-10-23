#include "my/my.h"

/**
 * @brief Reverse a null-terminated string in place.
 * @param str: string to reverse.
 * @return Pointer to str.
 */
char *my_revstr(char *str)
{
    int len = my_strlen(str);
    char tmp = 0;

    for (int i = 0; i < len / 2; i++) {
        tmp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = tmp;
    }
    return str;
}
