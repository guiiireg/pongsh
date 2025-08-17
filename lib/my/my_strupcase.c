// ============================
//        MY_STRUPCASE
// ============================
// Made by Guireg on 17/08/2025
// Last update: 17/08/2025
// ============================
#include "../../include/my.h"

char *my_strupcase(char *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] = str[i] - 32;
        i++;
    }
    return str;
}
