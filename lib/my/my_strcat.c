#include <stddef.h>

char *my_strcat(char *dest, const char *src) {
    int dest_len = 0;
    int i = 0;
    
    if (dest == NULL)
        return NULL;
    
    if (src == NULL)
        return dest;
    
    while (dest[dest_len] != '\0')
        dest_len++;
    
    while (src[i] != '\0') {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[dest_len + i] = '\0';
    
    return dest;
}