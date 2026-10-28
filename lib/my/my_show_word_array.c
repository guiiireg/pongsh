#include <stddef.h>

#include "my.h"

/**
** @brief Writes each word of an array to the standard output.
**
** Each word is followed by a newline.
**
** @param array The NULL-terminated word array to display.
**
** @return The number of words displayed, or -1 on failure.
*/
int my_show_word_array(char *const *array)
{
    int i = 0;

    if (array == NULL) {
        return (-1);
    }
    while (array[i] != NULL) {
        if (my_putstr(array[i]) == -1) {
            return (-1);
        }
        if (my_putchar('\n') == -1) {
            return (-1);
        }
        i += 1;
    }
    return (i);
}
