#include <stddef.h>

/**
 * @brief Finds the first occurrence of a substring in a string.
 *
 * @param str The string to search in.
 * @param needle The substring to find.
 *
 * @return A pointer to the first occurrence, to str if needle is empty,
 *         or NULL if not found.
 */
char *my_strstr(char const *str, char const *needle)
{
    int i = 0;
    int j;

    if (str == NULL || needle == NULL) {
        return (NULL);
    }
    if (needle[0] == '\0') {
        return ((char *)str);
    }
    while (str[i] != '\0') {
        j = 0;
        while (needle[j] != '\0' && str[i + j] == needle[j]) {
            j += 1;
        }
        if (needle[j] == '\0') {
            return ((char *)&str[i]);
        }
        i += 1;
    }
    return (NULL);
}
