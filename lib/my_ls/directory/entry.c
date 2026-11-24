#include "my_ls.h"
#include "my.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static char *entry_path(char const *name, char const *parent)
{
    size_t name_length = (size_t)my_strlen(name);
    size_t prefix = parent ? (size_t)my_strlen(parent) : 0;
    char *path;

    if (prefix && parent[prefix - 1] != '/')
        prefix++;
    if (prefix > SIZE_MAX - name_length - 1) {
        errno = ENOMEM;
        return NULL;
    }
    path = malloc(prefix + name_length + 1);
    if (!path)
        return NULL;
    if (prefix) {
        my_strcpy(path, parent);
        path[prefix - 1] = '/';
    }
    my_strcpy(path + prefix, name);
    return path;
}

static int load_info(ls_entry_t *entry, int follow)
{
    struct stat target;

    if (lstat(entry->path, &entry->info) < 0)
        return -1;
    if (follow && S_ISLNK(entry->info.st_mode)) {
        if (stat(entry->path, &target) == 0 && S_ISDIR(target.st_mode))
            entry->info = target;
    }
    return 0;
}

ls_entry_t *ls_create_entry(char const *name, char const *parent, int follow)
{
    ls_entry_t *entry = malloc(sizeof(*entry));

    if (!entry) {
        perror("my_ls");
        return NULL;
    }
    *entry = (ls_entry_t){.path = entry_path(name, parent)};
    if (entry->path && load_info(entry, follow) == 0) {
        entry->name = entry->path;
        if (parent)
            entry->name += my_strlen(entry->path) - my_strlen(name);
        return entry;
    }
    perror(entry->path ? entry->path : name);
    ls_free_entries(entry);
    return NULL;
}

void ls_free_entries(ls_entry_t *entry)
{
    ls_entry_t *next;

    while (entry) {
        next = entry->next;
        free(entry->path);
        free(entry);
        entry = next;
    }
}
