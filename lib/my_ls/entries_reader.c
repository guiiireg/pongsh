/**
 * ===================================================================
 *                              ENTRIES READER
 * ===================================================================
 * File: entries_reader.c
 * Description: Directory entry reading for my_ls implementation.
 * Dependencies: my_ls.h
 * ===================================================================
 */
#include "../../include/my_ls.h"

static int is_hidden_entry(const char *name, int show_hidden)
{
    return (!show_hidden && name[0] == '.');
}

static int add_entry_to_list(char **entries, int count, const char *name)
{
    entries[count] = my_strdup(name);
    if (!entries[count]) {
        return -1;
    }
    return 0;
}

int read_directory_entries(DIR *dir, char **entries, int show_hidden)
{
    struct dirent *entry;
    int count = 0;

    entry = readdir(dir);
    while (entry != NULL && count < 1024) {
        if (is_hidden_entry(entry->d_name, show_hidden)) {
            entry = readdir(dir);
            continue;
        }
        if (add_entry_to_list(entries, count, entry->d_name) == -1) {
            break;
        }
        entry = readdir(dir);
        count++;
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
