#include "my.h"

char *my_strstr(char *str, char const *to_find)
{
    int length = my_strlen(to_find);

    if (length == 0)
        return str;
    for (; *str; str++)
        if (my_strncmp(str, to_find, length) == 0)
            return str;
    return 0;
}
