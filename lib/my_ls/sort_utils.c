/**
 * ===================================================================
 *                              MY_LS SORT UTILS
 * ===================================================================
 * File: sort_utils.c
 * Description: Sorting logic for my_ls implementation.
 * Dependencies: my_ls.h
 * ===================================================================
 */
#include "../../include/my_ls.h"

static void my_swap(char **a, char **b)
{
    char *temp = *a;

    *a = *b;
    *b = temp;
}

static int compare_strings(const char *a, const char *b)
{
    return my_strcmp(a, b);
}

static void sort_entries_inner_loop(char **entries, int i, int count)
{
    int j;

    for (j = i + 1; j < count; j++) {
        if (compare_strings(entries[i], entries[j]) <= 0) {
            continue;
        }
        my_swap(&entries[i], &entries[j]);
    }
}

void sort_entries(char **entries, int count)
{
    int i;

    for (i = 0; i < count - 1; i++) {
        sort_entries_inner_loop(entries, i, count);
    }
}
