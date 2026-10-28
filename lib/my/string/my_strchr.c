#include <stddef.h>

/**
 * @brief Finds the first occurrence of a character in a string.
 *
 * @param str The string to search in.
 * @param c The character to find.
 *
 * @return A pointer to the first occurrence, to the terminating null
 *         byte if c is '\0', or NULL if not found.
 */
char *my_strchr(char const *str, int c)
{
    int i = 0;

    if (str == NULL) {
        return (NULL);
    }
    while (str[i] != '\0') {
        if (str[i] == c) {
            return ((char *)&str[i]);
        }
        i += 1;
    }
    if (c == '\0') {
        return ((char *)&str[i]);
    }
    return (NULL);
}
