#include "my_ls.h"

static void display_details(struct stat const *info)
{
    ls_mode(info->st_mode);
    ls_text(" ");
    ls_number(info->st_nlink);
    ls_text(" ");
    ls_owner(info);
    ls_text(" ");
    if (info->st_size < 0) {
        ls_text("-");
        ls_number(0 - (uintmax_t)info->st_size);
    } else {
        ls_number(info->st_size);
    }
    ls_text(" ");
    ls_date(info->st_mtime);
    ls_text(" ");
}

int ls_display(ls_entry_t const *entry, ls_options_t const *options)
{
    int status = 0;

    if (options->long_format)
        display_details(&entry->info);
    ls_text(entry->name);
    if (options->long_format && S_ISLNK(entry->info.st_mode))
        status = ls_link(entry);
    ls_text("\n");
    return status;
}
