#include <stddef.h>
#include <stdlib.h>

#include "word_array_internal.h"

/**
 * @brief Copies a word of the given length into a new string.
 *
 * @param str The start of the word to copy.
 * @param len The length of the word.
 *
 * @return A newly allocated string, or NULL on failure.
 */
static char *wa_copy_word(char const *str, int len)
{
    char *word = malloc(sizeof(char) * (len + 1));
    int i = 0;

    if (word == NULL) {
        return (NULL);
    }
    while (i < len) {
        word[i] = str[i];
        i += 1;
    }
    word[len] = '\0';
    return (word);
}

/**
 * @brief Fills one word of the array from the string.
 *
 * @param array The word array being filled.
 * @param word The index of the word to fill.
 * @param str The string to read from.
 * @param i The current position, advanced past the word.
 *
 * @return 0 on success, 1 when the string is exhausted, or -1 on
 *         failure.
 */
static int wa_fill_word(char **array, int word, char const *str, int *i)
{
    int len = 0;

    while (wa_is_separator(str[*i]) == 1) {
        *i += 1;
    }
    if (str[*i] == '\0') {
        return (1);
    }
    while (str[*i + len] != '\0' && wa_is_separator(str[*i + len]) == 0) {
        len += 1;
    }
    array[word] = wa_copy_word(&str[*i], len);
    if (array[word] == NULL) {
        return (-1);
    }
    *i += len;
    return (0);
}

/**
 * @brief Fills the whole word array from the string.
 *
 * The array is NULL-terminated. On failure, the words filled so far
 * remain allocated for my_free_word_array to release.
 *
 * @param array The word array to fill.
 * @param str The string to read from.
 *
 * @return 0 on success, or -1 on failure.
 */
int wa_fill_words(char **array, char const *str)
{
    int i = 0;
    int word = 0;
    int status = wa_fill_word(array, word, str, &i);

    while (status == 0) {
        word += 1;
        status = wa_fill_word(array, word, str, &i);
    }
    array[word] = NULL;
    if (status == -1) {
        return (-1);
    }
    return (0);
}
