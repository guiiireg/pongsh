#include "my_ls.h"
#include "my.h"
#include <dirent.h>
#include <errno.h>
#include <stdio.h>

static int add_entry(char const *name, char const *path, ls_entry_t **entries)
{
    ls_entry_t *entry = ls_create_entry(name, path, 0);

    if (!entry)
        return 1;
    entry->next = *entries;
    *entries = entry;
    return 0;
}

static int read_entries(DIR *dir, char const *path, ls_entry_t **entries,
    ls_options_t const *options)
{
    struct dirent *item;
    int status = 0;

    errno = 0;
    item = readdir(dir);
    while (item) {
        if (options->all || item->d_name[0] != '.')
            status |= add_entry(item->d_name, path, entries);
        errno = 0;
        item = readdir(dir);
    }
    if (errno) {
        perror(path);
        status = 1;
    }
    if (closedir(dir) < 0) {
        perror(path);
        status = 1;
    }
    return status;
}

static int display_entries(ls_entry_t const *entries,
    ls_options_t const *options, int *printed)
{
    int status = 0;
    ls_entry_t const *entry = entries;
    ls_columns_t columns = {0};

    if (options->long_format)
        ls_measure(&columns, entries, 0);
    while (entry) {
        status |= ls_display(entry, options, &columns);
        entry = entry->next;
    }
    *printed = 1;
    for (; entries && options->recursive; entries = entries->next) {
        if (S_ISDIR(entries->info.st_mode)
            && my_strcmp(entries->name, ".") && my_strcmp(entries->name, ".."))
            status |= ls_list_directory(entries->path, options, 1, printed);
    }
    return status;
}

int ls_list_directory(char const *path, ls_options_t const *options,
    int header, int *printed)
{
    DIR *dir = opendir(path);
    ls_entry_t *entries = NULL;
    int status;

    if (!dir) {
        perror(path);
        return 1;
    }
    status = read_entries(dir, path, &entries, options);
    if (header)
        ls_header(path, printed);
    entries = ls_sort(entries, options);
    status |= display_entries(entries, options, printed);
    ls_free_entries(entries);
    return status;
}
