/**
 * ===================================================================
 *                              ENTRIES FORMATTER
 * ===================================================================
 * File: entries_formatter.c
 * Description: Formatting utilities for my_ls entries display.
 * Dependencies: my_ls.h
 * ===================================================================
 */
#include "../../include/my_ls.h"

int find_max_length(char **entries, int count)
{
    int max_len = 0;
    int len;
    int i;

    for (i = 0; i < count; i++) {
        len = my_strlen(entries[i]);
        if (len > max_len) {
            max_len = len;
        }
    }
    return max_len;
}

void calculate_columns_layout(int count, int max_len, int *columns, int *rows)
{
    int terminal_width = 80;
    int col_width = max_len + 2;

    *columns = terminal_width / col_width;
    if (*columns < 1) {
        *columns = 1;
    }
    if (*columns > count) {
        *columns = count;
    }
    *rows = (count + *columns - 1) / *columns;
}

void print_padding_spaces(int count)
{
    int i;

    for (i = 0; i < count; i++) {
        my_printf(" ");
    }
}

void print_colored_with_padding(const char *path, const char *filename, int width)
{
    int len = my_strlen(filename);
    int padding;

    print_colored_filename(path, filename);
    padding = width - len;
    print_padding_spaces(padding);
}
