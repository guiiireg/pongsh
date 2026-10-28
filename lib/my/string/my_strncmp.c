#include <stddef.h>

/**
** @brief Compares the first n characters of two strings.
**
** @param s1 The first string.
** @param s2 The second string.
** @param n The maximum number of characters to compare.
**
** @return A negative value if the segment of s1 is lower, 0 if the
**         segments are equal, a positive value if the segment of s1 is
**         greater, or -1 on failure.
*/
int my_strncmp(char const *s1, char const *s2, int n)
{
    int i = 0;

    if (s1 == NULL || s2 == NULL || n < 0) {
        return (-1);
    }
    while (i < n && s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i]) {
        i += 1;
    }
    if (i == n) {
        return (0);
    }
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
