#include "my_ls.h"
#include "my.h"

static int before(ls_entry_t const *a, ls_entry_t const *b,
    ls_options_t const *options)
{
    int cmp = 0;

    if (options->by_time && a->info.st_mtim.tv_sec != b->info.st_mtim.tv_sec)
        cmp = 1 - 2 * (a->info.st_mtim.tv_sec > b->info.st_mtim.tv_sec);
    if (options->by_time && !cmp
        && a->info.st_mtim.tv_nsec != b->info.st_mtim.tv_nsec)
        cmp = 1 - 2 * (a->info.st_mtim.tv_nsec > b->info.st_mtim.tv_nsec);
    if (!cmp)
        cmp = my_strcmp(a->name, b->name);
    if (options->reverse)
        return cmp >= 0;
    return cmp <= 0;
}

static ls_entry_t *merge(ls_entry_t *left, ls_entry_t *right,
    ls_options_t const *options)
{
    ls_entry_t *head = NULL;
    ls_entry_t **tail = &head;

    while (left && right) {
        if (before(left, right, options)) {
            *tail = left;
            left = left->next;
        } else {
            *tail = right;
            right = right->next;
        }
        tail = &(*tail)->next;
    }
    *tail = left;
    if (right)
        *tail = right;
    return head;
}

ls_entry_t *ls_sort(ls_entry_t *entries, ls_options_t const *options)
{
    ls_entry_t *middle = entries;
    ls_entry_t *fast;
    ls_entry_t *right;

    if (!entries || !entries->next)
        return entries;
    fast = entries->next;
    while (fast && fast->next) {
        middle = middle->next;
        fast = fast->next->next;
    }
    right = middle->next;
    middle->next = NULL;
    return merge(ls_sort(entries, options), ls_sort(right, options), options);
}
