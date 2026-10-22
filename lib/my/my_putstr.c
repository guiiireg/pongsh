#include <unistd.h>

int my_putstr(const char *str) {
    int count = 0;
    
    if (str == NULL)
        return 0;
    
    while (str[count] != '\0') {
        write(1, &str[count], 1);
        count++;
    }
    
    return count;
}