#include "my_ls.h"
#include "my.h"
#include <pwd.h>

char const *ls_owner(uid_t uid, char *fallback)
{
    struct passwd *user = getpwuid(uid);

    if (user)
        return user->pw_name;
    ls_decimal(fallback, uid);
    return fallback;
}

static char const *french_month(char const *date)
{
    char const months[] = "JanFebMarAprMayJunJulAugSepOctNovDec";
    char const *const labels[] = {"janv.", "févr.", "mars ", "avr. ", "mai  ",
        "juin ", "juil.", "août ", "sept.", "oct. ", "nov. ", "déc. "};
    size_t index;

    for (index = 0; index < sizeof(labels) / sizeof(labels[0]); index++) {
        if (!my_strncmp(date + 4, months + index * 3, 3))
            return labels[index];
    }
    return "?    ";
}

void ls_date(time_t modified)
{
    time_t now = time(NULL);
    char const *date = ctime(&modified);

    if (!date) {
        ls_text("?              ");
        return;
    }
    ls_write(date + 8, 3);
    ls_text(french_month(date));
    ls_text(" ");
    if (now >= modified
        && (uintmax_t)now - (uintmax_t)modified > LS_HALF_YEAR) {
        ls_text(" ");
        ls_write(date + 20, 4);
        return;
    }
    ls_write(date + 11, 5);
}
