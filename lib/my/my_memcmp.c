#include <stddef.h>

/**
** @brief Compares two memory areas.
**
** @param s1 The first memory area.
** @param s2 The second memory area.
** @param n The number of bytes to compare.
**
** @return A negative value if s1 is lower, 0 if the areas are equal,
**         a positive value if s1 is greater, or -1 on failure.
*/
int my_memcmp(void const *s1, void const *s2, int n)
{
    int i = 0;
    unsigned char const *bytes1 = s1;
    unsigned char const *bytes2 = s2;

    if (s1 == NULL || s2 == NULL || n < 0) {
        return (-1);
    }
    while (i < n && bytes1[i] == bytes2[i]) {
        i += 1;
    }
    if (i == n) {
        return (0);
    }
    return (bytes1[i] - bytes2[i]);
}
