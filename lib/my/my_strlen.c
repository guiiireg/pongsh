#include <stddef.h>

int my_strlen(const char *str) {
    int count = 0;
    
    if (str == NULL)
        return 0;
    
    while (str[count] != '\0') {
        count++;
    }
    
    return count;
}