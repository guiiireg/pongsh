#include "my_ls.h"
#include "my.h"

static void measure_entry(ls_columns_t *columns, ls_entry_t const *entry)
{
    char size[LS_SIZE_BUFFER];
    char fallback[LS_SIZE_BUFFER];
    char const *owner = ls_owner(entry->info.st_uid, fallback);
    size_t owner_width = (size_t)my_strlen(owner);
    size_t size_width;

    ls_size(size, &entry->info);
    size_width = (size_t)my_strlen(size);
    if (size_width > columns->size)
        columns->size = size_width;
    if (owner_width > columns->owner)
        columns->owner = owner_width;
}

void ls_measure(ls_columns_t *columns, ls_entry_t const *entries,
    int skip_directories)
{
    *columns = (ls_columns_t){0};
    while (entries) {
        if (!skip_directories || !S_ISDIR(entries->info.st_mode))
            measure_entry(columns, entries);
        entries = entries->next;
    }
}
