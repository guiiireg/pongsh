#include <stddef.h>

/**
 * @brief Compares two strings lexicographically.
 *
 * @param s1 The first string.
 * @param s2 The second string.
 *
 * @return A negative value if s1 is lower, 0 if the strings are equal,
 *         a positive value if s1 is greater, or -1 on failure.
 */
int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;

    if (s1 == NULL || s2 == NULL) {
        return (-1);
    }
    while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i]) {
        i += 1;
    }
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
