#include "my.h"

static int is_alphanumeric(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
        || (c >= '0' && c <= '9');
}

char *my_strcapitalize(char *str)
{
    int word_start = 1;

    my_strlowcase(str);
    for (char *current = str; *current; current++) {
        if (word_start && *current >= 'a' && *current <= 'z')
            *current -= 'a' - 'A';
        word_start = !is_alphanumeric(*current);
    }
    return str;
}
