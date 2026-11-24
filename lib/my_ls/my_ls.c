#include "my_ls.h"

static int list_operands(ls_entry_t *entries, ls_options_t const *options,
    int multiple)
{
    ls_entry_t *entry = entries;
    int printed = 0;
    int status = 0;

    while (entry) {
        if (options->directory || !S_ISDIR(entry->info.st_mode)) {
            status |= ls_display(entry, options);
            printed = 1;
        }
        entry = entry->next;
    }
    while (entries && !options->directory) {
        if (S_ISDIR(entries->info.st_mode))
            status |= ls_list_directory(entries->path, options,
                multiple || options->recursive, &printed);
        entries = entries->next;
    }
    return status;
}

static int collect_operand(char const *name, ls_entry_t **entries,
    ls_options_t const *options)
{
    ls_entry_t *entry = ls_create_entry(name, NULL,
        !options->long_format && !options->directory);

    if (!entry)
        return 1;
    entry->next = *entries;
    *entries = entry;
    return 0;
}

int main(int argc, char **argv)
{
    ls_options_t options = {0};
    ls_entry_t *entries = NULL;
    int count = ls_parse_options(argc, argv, &options);
    int index;
    int status = 0;

    if (count < 0)
        return 2;
    if (!count)
        status = collect_operand(".", &entries, &options);
    for (index = 0; index < count; index++)
        status |= collect_operand(argv[index + 1], &entries, &options);
    entries = ls_sort(entries, &options);
    status |= list_operands(entries, &options, count > 1);
    ls_free_entries(entries);
    return status;
}
