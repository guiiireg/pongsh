#include "my.h"

int my_showstr(char const *str)
{
    static char const hex[] = "0123456789abcdef";
    unsigned char byte;

    for (; *str; str++) {
        byte = (unsigned char)*str;
        if (byte >= 32 && byte <= 126) {
            my_putchar(byte);
        } else {
            my_putchar('\\');
            my_putchar(hex[byte >> 4]);
            my_putchar(hex[byte & 15]);
        }
    }
    return 0;
}
