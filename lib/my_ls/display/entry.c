#include "my_ls.h"
#include "my.h"

static void display_details(struct stat const *info, ls_columns_t const *width)
{
    char size[LS_SIZE_BUFFER];
    char fallback[LS_SIZE_BUFFER];
    char const *owner = ls_owner(info->st_uid, fallback);
    size_t owner_width = (size_t)my_strlen(owner);
    size_t size_width;

    ls_size(size, info);
    size_width = (size_t)my_strlen(size);
    ls_mode(info->st_mode);
    ls_text(" ");
    if (width->size > size_width)
        ls_spaces(width->size - size_width);
    ls_text(size);
    ls_text(" ");
    ls_text(owner);
    if (width->owner > owner_width)
        ls_spaces(width->owner - owner_width);
    ls_text(" ");
    ls_date(info->st_mtime);
}

int ls_display(ls_entry_t const *entry, ls_options_t const *options,
    ls_columns_t const *columns)
{
    int status = 0;

    if (options->long_format) {
        display_details(&entry->info, columns);
        ls_text(" ");
        ls_text(ls_icon(entry));
        ls_text(" ");
    }
    ls_text(entry->name);
    if (options->long_format && S_ISLNK(entry->info.st_mode))
        status = ls_link(entry);
    ls_text("\n");
    return status;
}
