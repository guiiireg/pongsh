// ============================
//        MY_STR_ISPRINTABLE
// ============================
// Made by Guireg on 17/08/2025
// Last update: 17/08/2025
// ============================
#include "../../include/my.h"

int my_str_isprintable(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] < 32 || str[i] > 126)
            return 0;
        i++;
    }
    return 1;
}
