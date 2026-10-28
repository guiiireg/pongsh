#include <stddef.h>
#include <stdlib.h>

/**
 * @brief Frees a word array and its words.
 *
 * @param array The NULL-terminated word array to free.
 */
void my_free_word_array(char **array)
{
    int i = 0;

    if (array == NULL) {
        return;
    }
    while (array[i] != NULL) {
        free(array[i]);
        i += 1;
    }
    free(array);
}
