#include <stdlib.h>
#include <stddef.h>

char *my_strdup(const char *s) {
    char *dup;
    int len = 0;
    
    if (s == NULL)
        return NULL;
    
    while (s[len] != '\0')
        len++;
    
    dup = malloc(len + 1);
    if (dup == NULL)
        return NULL;
    
    for (int i = 0; i <= len; i++)
        dup[i] = s[i];
    
    return dup;
}