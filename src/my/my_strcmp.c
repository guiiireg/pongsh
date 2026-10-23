#include "my/my.h"

/**
 * @brief Compare two null-terminated strings byte by byte.
 * @param s1: first string.
 * @param s2: second string.
 * @return Difference between the first differing bytes.
 */
int my_strcmp(const char *s1, const char *s2)
{
    int i = 0;

    while (s1[i] == s2[i] && s1[i] != '\0')
        i++;
    return s1[i] - s2[i];
}
