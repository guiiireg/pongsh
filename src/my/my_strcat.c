#include "my/my.h"

/**
 * @brief Append a null-terminated string to another.
 * @param dest: destination buffer, must be large enough.
 * @param src: string to append.
 * @return Pointer to dest.
 */
char *my_strcat(char *dest, const char *src)
{
    my_strcpy(dest + my_strlen(dest), src);
    return dest;
}
