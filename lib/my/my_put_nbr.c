#include <unistd.h>

int my_put_nbr(int n) {
    int count = 0;
    char buffer[12];
    int i = 0;
    
    if (n == 0) {
        write(1, "0", 1);
        return 1;
    }
    
    if (n < 0) {
        write(1, "-", 1);
        count++;
        if (n == -2147483648) {
            write(1, "2147483648", 10);
            return 11;
        }
        n = -n;
    }
    
    while (n > 0) {
        buffer[i] = (n % 10) + '0';
        n /= 10;
        i++;
    }
    
    while (i > 0) {
        i--;
        write(1, &buffer[i], 1);
        count++;
    }
    
    return count;
}