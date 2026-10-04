#include "../../include/shell.h"

int is_empty_line(const char *str)
{
    if (str == NULL)
        return (1);
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
            return (0);
    }
    return (1);
}
