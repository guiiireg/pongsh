#include <stddef.h>

int my_strcmp(const char *s1, const char *s2) {
    int i = 0;
    
    if (s1 == NULL && s2 == NULL)
        return 0;
    if (s1 == NULL)
        return -1;
    if (s2 == NULL)
        return 1;
    
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i])
            return (unsigned char)s1[i] - (unsigned char)s2[i];
        i++;
    }
    
    return (unsigned char)s1[i] - (unsigned char)s2[i];
}