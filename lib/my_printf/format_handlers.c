// ============================
//        FORMAT_HANDLERS
// ============================
// Made by Guireg on 17/08/2025
// Last update: 17/08/2025
// ============================
#include "../../include/my.h"

int handle_char(va_list args)
{
    char c = va_arg(args, int);

    my_putchar(c);
    return 1;
}

int handle_string(va_list args)
{
    char *str = va_arg(args, char *);

    if (str == NULL) {
        return my_putstr("(null)");
    }
    return my_putstr(str);
}

int handle_integer(va_list args)
{
    int num = va_arg(args, int);

    return my_put_nbr(num);
}

int handle_percent(void)
{
    my_putchar('%');
    return 1;
}
