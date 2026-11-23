#include "my.h"
#include <unistd.h>

void my_putchar(char c)
{
    (void)write(STDOUT_FILENO, &c, 1);
}
