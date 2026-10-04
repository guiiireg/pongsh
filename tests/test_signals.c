#include <criterion/criterion.h>
#include "../include/shell.h"

Test(signals, restore_signals)
{
    struct sigaction sa = {0};

    setup_parent_signals();
    restore_child_signals();
    sigaction(SIGINT, NULL, &sa);
    cr_assert_eq(sa.sa_handler, SIG_DFL);
    sigaction(SIGTSTP, NULL, &sa);
    cr_assert_eq(sa.sa_handler, SIG_DFL);
}

Test(signals, parent_signals)
{
    struct sigaction sa = {0};

    setup_parent_signals();
    sigaction(SIGTSTP, NULL, &sa);
    cr_assert_eq(sa.sa_handler, SIG_IGN);
    sigaction(SIGINT, NULL, &sa);
    cr_assert_neq(sa.sa_handler, SIG_DFL);
}
