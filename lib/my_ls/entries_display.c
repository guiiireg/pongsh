/**
 * ===================================================================
 *                              ENTRIES DISPLAY
 * ===================================================================
 * File: entries_display.c
 * Description: Column display for my_ls entries.
 * Dependencies: my_ls.h
 * ===================================================================
 */
#include "../../include/my_ls.h"

static void print_entry_at_position(char **entries, int count, const char *dir_path,
    int columns, int rows, int row, int col, int col_width)
{
    int index = col * rows + row;

    if (index < count) {
        if (col == columns - 1) {
            print_colored_filename(dir_path, entries[index]);
        } else {
            print_colored_with_padding(dir_path, entries[index], col_width);
        }
    }
}

static void print_single_row(char **entries, int count, const char *dir_path,
    int columns, int rows, int row, int col_width)
{
    int col;

    for (col = 0; col < columns; col++) {
        print_entry_at_position(entries, count, dir_path, columns, rows, row, col, col_width);
    }
    my_printf("\n");
}

void display_entries_in_columns(char **entries, int count, const char *dir_path)
{
    int max_len;
    int columns, rows, col_width;
    int row;

    if (count == 0) {
        return;
    }
    max_len = find_max_length(entries, count);
    col_width = max_len + 2;
    calculate_columns_layout(count, max_len, &columns, &rows);
    for (row = 0; row < rows; row++) {
        print_single_row(entries, count, dir_path, columns, rows, row, col_width);
    }
}

void display_detailed_entries(char **entries, int count, const char *dir_path)
{
    int i;

    for (i = 0; i < count; i++) {
        print_file_info(entries[i], dir_path, 1);
    }
}
