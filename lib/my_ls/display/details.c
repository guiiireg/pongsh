#include "my_ls.h"
#include <grp.h>
#include <pwd.h>
#include <time.h>

#define LS_HALF_YEAR 15778476u

void ls_owner(struct stat const *info)
{
    struct passwd *user = getpwuid(info->st_uid);
    struct group *group;

    if (user)
        ls_text(user->pw_name);
    else
        ls_number(info->st_uid);
    ls_text(" ");
    group = getgrgid(info->st_gid);
    if (group)
        ls_text(group->gr_name);
    else
        ls_number(info->st_gid);
}

void ls_date(time_t modified)
{
    time_t now = time(NULL);
    char const *date = ctime(&modified);

    if (!date) {
        ls_text("?");
        return;
    }
    ls_write(date + 4, 7);
    if (now >= modified
        && (uintmax_t)now - (uintmax_t)modified <= LS_HALF_YEAR) {
        ls_write(date + 11, 5);
        return;
    }
    ls_text(" ");
    ls_write(date + 20, 4);
}
