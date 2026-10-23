#include "my/my.h"

/**
 * @brief Compare the first n bytes of two strings.
 * @param s1: first string.
 * @param s2: second string.
 * @param n: maximum number of bytes to compare.
 * @return Difference between the first differing bytes.
 */
int my_strncmp(const char *s1, const char *s2, int n)
{
    int i = 0;

    while (i < n && s1[i] == s2[i] && s1[i] != '\0')
        i++;
    if (i == n)
        return 0;
    return s1[i] - s2[i];
}
