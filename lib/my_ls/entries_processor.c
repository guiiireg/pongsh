/**
 * ===================================================================
 *                              ENTRIES PROCESSOR
 * ===================================================================
 * File: entries_processor.c
 * Description: Main processing coordination for my_ls entries.
 * Dependencies: my_ls.h
 * ===================================================================
 */
#include "../../include/my_ls.h"

void display_entries(char **entries, int count, const char *dir_path, int show_details)
{
    if (show_details) {
        display_detailed_entries(entries, count, dir_path);
    } else {
        display_entries_in_columns(entries, count, dir_path);
    }
    free_entries(entries, count);
}

void process_directory_entries(DIR *dir, const char *dir_path,
    int show_hidden, int show_details)
{
    char *entries[1024];
    int count;

    count = read_directory_entries(dir, entries, show_hidden);
    sort_entries(entries, count);
    display_entries(entries, count, dir_path, show_details);
}
