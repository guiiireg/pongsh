#include "my_ls.h"
#include "my.h"

static char const *basename_of(char const *name)
{
    char const *base = name;

    while (*name) {
        if (*name == '/' && name[1] && name[1] != '/')
            base = name + 1;
        name++;
    }
    return base;
}

static int named_directory(char const *name, char const *label)
{
    int length = my_strlen(label);

    if (my_strncmp(name, label, length))
        return 0;
    name += length;
    while (*name == '/')
        name++;
    return !*name;
}

static char const *directory_icon(char const *name)
{
    if (named_directory(name, ".git"))
        return "\ue5fb";
    if (named_directory(name, ".github"))
        return "\ue5fd";
    if (named_directory(name, "include"))
        return "\ue5fc";
    if (named_directory(name, "src"))
        return "\U000f08de";
    return "\ue5ff";
}

static int has_suffix(char const *name, char const *suffix)
{
    int length = my_strlen(name);
    int size = my_strlen(suffix);

    return length >= size && !my_strcmp(name + length - size, suffix);
}

static char const *file_icon(char const *name, mode_t mode)
{
    if (S_ISLNK(mode))
        return "\uf481";
    if (!my_strcmp(name, ".gitignore"))
        return "\U000f02a2";
    if (!my_strcmp(name, "README.md"))
        return "\U000f00ba";
    if (!my_strcmp(name, "Makefile"))
        return "\ue673";
    if (has_suffix(name, ".md"))
        return "\uf48a";
    if (has_suffix(name, ".log"))
        return "\uf18d";
    if (has_suffix(name, ".sh"))
        return "\uf489";
    if (S_ISREG(mode) && (mode & (S_IXUSR | S_IXGRP | S_IXOTH)))
        return "\U000f086f";
    return "\uf15b";
}

char const *ls_icon(ls_entry_t const *entry)
{
    char const *name = basename_of(entry->name);

    if (S_ISDIR(entry->info.st_mode))
        return directory_icon(name);
    return file_icon(name, entry->info.st_mode);
}
