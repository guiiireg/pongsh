#include "my_ls.h"

static char file_type(mode_t mode)
{
    if (S_ISDIR(mode))
        return 'd';
    if (S_ISLNK(mode))
        return 'l';
    if (S_ISCHR(mode))
        return 'c';
    if (S_ISBLK(mode))
        return 'b';
    if (S_ISFIFO(mode))
        return 'p';
    if (S_ISSOCK(mode))
        return 's';
    return '-';
}

static void set_special(char *access, mode_t mode)
{
    if (mode & S_ISUID)
        access[3] = access[3] == 'x' ? 's' : 'S';
    if (mode & S_ISGID)
        access[6] = access[6] == 'x' ? 's' : 'S';
    if (mode & S_ISVTX)
        access[9] = access[9] == 'x' ? 't' : 'T';
}

void ls_mode(mode_t mode)
{
    char access[] = "----------";
    char const letters[] = "rwx";
    mode_t bit = S_IRUSR;
    size_t index;

    access[0] = file_type(mode);
    for (index = 0; index < 9; index++) {
        if (mode & bit)
            access[index + 1] = letters[index % 3];
        bit >>= 1;
    }
    set_special(access, mode);
    ls_text(access);
}
