#include "../../include/shell.h"

static void sigint_handler(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\n", 1);
    display_prompt();
}

void setup_parent_signals(void)
{
    struct sigaction sa = {0};

    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);
    signal(SIGTSTP, SIG_IGN);
}

void restore_child_signals(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGTSTP, SIG_DFL);
}
