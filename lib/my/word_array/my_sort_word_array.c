#include <stddef.h>

#include "my.h"

static int compare_words(void const *a, void const *b)
{
    char *const *left = a;
    char *const *right = b;

    return (my_strcmp(*left, *right));
}

/**
 * @brief Sorts a NULL-terminated word array in lexicographic order.
 *
 * @param array The word array to sort.
 *
 * @return 0 on success, or -1 on failure.
 */
int my_sort_word_array(char **array)
{
    int count = 0;

    if (array == NULL) {
        return (-1);
    }
    while (array[count] != NULL) {
        count += 1;
    }
    my_sort(array, count, (int)sizeof(char *), compare_words);
    return (0);
}
