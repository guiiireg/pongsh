#include <stddef.h>
#include <stdlib.h>

#include "my.h"

static int is_separator(char c)
{
    if (c == ' ' || c == '\t' || c == '\n') {
        return (1);
    }
    return (0);
}

static int count_words(char const *str)
{
    int count = 0;
    int i = 0;
    int in_word = 0;

    while (str[i] != '\0') {
        if (is_separator(str[i]) == 1) {
            in_word = 0;
        } else if (in_word == 0) {
            in_word = 1;
            count += 1;
        }
        i += 1;
    }
    return (count);
}

static char *copy_word(char const *str, int len)
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

static int fill_word(char **array, int word, char const *str, int *i)
{
    int len = 0;

    while (is_separator(str[*i]) == 1) {
        *i += 1;
    }
    if (str[*i] == '\0') {
        return (1);
    }
    while (str[*i + len] != '\0' && is_separator(str[*i + len]) == 0) {
        len += 1;
    }
    array[word] = copy_word(&str[*i], len);
    if (array[word] == NULL) {
        return (-1);
    }
    *i += len;
    return (0);
}

static int fill_words(char **array, char const *str)
{
    int i = 0;
    int word = 0;
    int status = fill_word(array, word, str, &i);

    while (status == 0) {
        word += 1;
        status = fill_word(array, word, str, &i);
    }
    array[word] = NULL;
    if (status == -1) {
        return (-1);
    }
    return (0);
}

/**
** @brief Splits a string into an array of words.
**
** Words are separated by spaces, tabs and newlines. Consecutive
** separators are treated as one. The returned array is NULL-terminated
** and must be released with my_free_word_array.
**
** @param str The string to split.
**
** @return A newly allocated NULL-terminated array of words, or NULL
**         on failure.
*/
char **my_str_to_word_array(char const *str)
{
    char **array;

    if (str == NULL) {
        return (NULL);
    }
    array = malloc(sizeof(char *) * (count_words(str) + 1));
    if (array == NULL) {
        return (NULL);
    }
    if (fill_words(array, str) == -1) {
        my_free_word_array(array);
        return (NULL);
    }
    return (array);
}
