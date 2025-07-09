/**
 * ===================================================================
 *                              MY_LS FLAGS UTILS
 * ===================================================================
 * File: flags_utils.c
 * Description: Flag parsing logic for my_ls implementation.
 * Dependencies: my_ls.h
 * ===================================================================
 */
#include "../../include/my_ls.h"

void parse_ls_flags(const char *flags, int *show_hidden, int *show_details)
{
    int i = 0;

    if (!flags) {
        return;
    }
    while (flags[i]) {
        switch (flags[i]) {
            case 'a':
                *show_hidden = 1;
                break;
            case 'l':
                *show_details = 1;
                break;
        }
        i++;
    }
}
