// ============================
//        MY_STRCAPITALIZE
// ============================
// Made by Guireg on 17/08/2025
// Last update: 17/08/2025
// ============================
#include "../../include/my.h"

static void handle_letter(char *str, int i, int capitalize_next)
{
    if (capitalize_next && str[i] >= 'a' && str[i] <= 'z') {
        str[i] = str[i] - 32;
    }
    if (!capitalize_next && str[i] >= 'A' && str[i] <= 'Z') {
        str[i] = str[i] + 32;
    }
}

char *my_strcapitalize(char *str)
{
    int i = 0;
    int capitalize_next = 1;

    while (str[i] != '\0') {
        if ((str[i] >= 'a' && str[i] <= 'z') ||
        (str[i] >= 'A' && str[i] <= 'Z')) {
            handle_letter(str, i, capitalize_next);
            capitalize_next = 0;
        } else {
            capitalize_next = 1;
        }
        i++;
    }
    return str;
}
