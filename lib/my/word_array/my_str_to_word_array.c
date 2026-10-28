#include <stdlib.h>

#include "my.h"
#include "word_array_internal.h"

/**
 * @brief Checks whether a character separates two words.
 *
 * @param c The character to check.
 *
 * @return 1 if the character is a separator, 0 otherwise.
 */
int wa_is_separator(char c)
{
    if (c == ' ' || c == '\t' || c == '\n') {
        return (1);
    }
    return (0);
}

/**
 * @brief Counts the words of a string.
 *
 * Consecutive separators are treated as one.
 *
 * @param str The string to scan.
 *
 * @return The number of words in the string.
 */
static int wa_count_words(char const *str)
{
    int count = 0;
    int i = 0;
    int in_word = 0;

    while (str[i] != '\0') {
        if (wa_is_separator(str[i]) == 1) {
            in_word = 0;
        } else if (in_word == 0) {
            in_word = 1;
            count += 1;
        }
        i += 1;
    }
    return (count);
}

/**
 * @brief Splits a string into an array of words.
 *
 * Words are separated by spaces, tabs and newlines. Consecutive
 * separators are treated as one. The returned array is NULL-terminated
 * and must be released with my_free_word_array.
 *
 * @param str The string to split.
 *
 * @return A newly allocated NULL-terminated array of words, or NULL
 *         on failure.
 */
char **my_str_to_word_array(char const *str)
{
    char **array;

    if (str == NULL) {
        return (NULL);
    }
    array = malloc(sizeof(char *) * (wa_count_words(str) + 1));
    if (array == NULL) {
        return (NULL);
    }
    if (wa_fill_words(array, str) == -1) {
        my_free_word_array(array);
        return (NULL);
    }
    return (array);
}
