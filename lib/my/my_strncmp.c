#include "my.h"

int my_strncmp(char const *s1, char const *s2, int n)
{
    for (int index = 0; index < n; index++) {
        if (s1[index] != s2[index])
            return (unsigned char)s1[index] - (unsigned char)s2[index];
        if (!s1[index])
            return 0;
    }
    return 0;
}
