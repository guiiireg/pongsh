#include "my/my.h"

static int is_letter(char c)
{
    if (c >= 'a' && c <= 'z')
        return 1;
    if (c >= 'A' && c <= 'Z')
        return 1;
    return 0;
}

/**
 * @brief Capitalize the first letter of each word, lowercase the rest.
 * @param str: string to modify in place.
 * @return Pointer to str.
 */
char *my_strcapitalize(char *str)
{
    int in_word = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (is_letter(str[i]) == 0) {
            in_word = 0;
            continue;
        }
        if (in_word == 0 && str[i] >= 'a' && str[i] <= 'z')
            str[i] -= 32;
        if (in_word == 1 && str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 32;
        in_word = 1;
    }
    return str;
}
