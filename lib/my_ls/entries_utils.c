/**
 * ===================================================================
 *                              MY_LS ENTRIES UTILS
 * ===================================================================
 * File: entries_utils.c
 * Description: Directory entry reading, freeing, displaying, and
 *              processing for my_ls.
 * Dependencies: my_ls.h
 * ===================================================================
 */
#include "../../include/my_ls.h"

int read_directory_entries(DIR *dir, char **entries, int show_hidden)
{
    struct dirent *entry;
    int count = 0;

    entry = readdir(dir);
    while (entry != NULL && count < 1024) {
        if (!show_hidden && entry->d_name[0] == '.') {
            entry = readdir(dir);
            continue;
        }
        entries[count] = my_strdup(entry->d_name);
        if (!entries[count]) {
            break;
        }
        count++;
        entry = readdir(dir);
    }
    return count;
}

void free_entries(char **entries, int count)
{
    int i;

    for (i = 0; i < count; i++) {
        my_free(entries[i]);
    }
}

void display_entries(char **entries, int count, const char *dir_path,
    int show_details)
{
    int i;

    for (i = 0; i < count; i++) {
        if (show_details) {
            print_file_info(entries[i], dir_path, 1);
        } else {
            my_printf("%s  ", entries[i]);
        }
    }
    if (!show_details) {
        my_printf("\n");
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
