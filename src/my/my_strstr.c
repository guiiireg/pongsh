#include "my/my.h"

static int starts_with(const char *str, const char *prefix)
{
    int i = 0;

    while (prefix[i] != '\0') {
        if (str[i] != prefix[i])
            return 0;
        i++;
    }
    return 1;
}

/**
 * @brief Find the first occurrence of a substring in a string.
 * @param str: string to search in.
 * @param to_find: substring to look for.
 * @return Pointer to the first occurrence, NULL if not found.
 */
char *my_strstr(char *str, const char *to_find)
{
    int i = 0;

    if (to_find[0] == '\0')
        return str;
    while (str[i] != '\0') {
        if (starts_with(&str[i], to_find))
            return &str[i];
        i++;
    }
    return NULL;
}
