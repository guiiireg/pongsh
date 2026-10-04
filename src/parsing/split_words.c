#include "../../include/shell.h"

static size_t count_words(const char *str)
{
    size_t count = 0;
    int in_word = 0;

    for (size_t i = 0; str[i] != '\0'; i++) {
        if (!IS_DELIM(str[i]) && !in_word) {
            in_word = 1;
            count++;
        }
        if (IS_DELIM(str[i]))
            in_word = 0;
    }
    return (count);
}

static size_t get_word_len(const char *str)
{
    size_t len = 0;

    while (str[len] != '\0' && !IS_DELIM(str[len]))
        len++;
    return (len);
}

static char *extract_word(const char *str, size_t len)
{
    char *word = malloc(sizeof(char) * (len + 1));

    if (word == NULL)
        return (NULL);
    for (size_t i = 0; i < len; i++)
        word[i] = str[i];
    word[len] = '\0';
    return (word);
}

static void fill_words(char **arr, const char *str)
{
    size_t idx = 0;
    size_t i = 0;
    size_t len = 0;

    while (str[i] != '\0') {
        if (!IS_DELIM(str[i])) {
            len = get_word_len(&str[i]);
            arr[idx++] = extract_word(&str[i], len);
            i += len;
        } else
            i++;
    }
    arr[idx] = NULL;
}

char **split_words(const char *str)
{
    char **arr = NULL;
    size_t count = 0;

    if (str == NULL)
        return (NULL);
    count = count_words(str);
    arr = malloc(sizeof(char *) * (count + 1));
    if (arr == NULL)
        return (NULL);
    fill_words(arr, str);
    return (arr);
}
