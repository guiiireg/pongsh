#include "../../include/my.h"

int my_putstr(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        my_putchar(str[i]);
    }
    return 0;
}

int main(void)
{
    my_putstr("Hello world");
}
