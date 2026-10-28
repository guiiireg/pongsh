#ifndef WORD_ARRAY_INTERNAL_H_
    #define WORD_ARRAY_INTERNAL_H_

/*
 * Internal helpers of the word_array module.
 *
 * These functions are shared between the word_array source files and
 * are not part of the public libmy API. Their names are prefixed with
 * wa_ to avoid polluting the library namespace.
 */

int wa_is_separator(char c);
int wa_fill_words(char **array, char const *str);

#endif // WORD_ARRAY_INTERNAL_H_
