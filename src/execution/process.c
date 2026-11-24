#include "pongsh.h"
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

static int wait_result(pid_t child)
{
    int status;
    pid_t result;

    do {
        result = waitpid(child, &status, 0);
    } while (result < 0 && errno == EINTR);
    if (result < 0) {
        perror("pongsh: waitpid");
        return 1;
    }
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    if (WIFSIGNALED(status)) {
        if (WTERMSIG(status) != SIGINT)
            sh_error("pongsh", strsignal(WTERMSIG(status)));
        return SH_SIGNAL_STATUS + WTERMSIG(status);
    }
    return 1;
}

static void run_child(char **args, char **env)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    sh_exec_path(args, env);
    exit(126);
}

int sh_external(shell_t *shell, char **args)
{
    pid_t child;
    int result = 1;

    if (shell->interactive)
        signal(SIGINT, SIG_IGN);
    child = fork();
    if (child < 0)
        perror("pongsh: fork");
    if (!child)
        run_child(args, shell->env);
    if (child > 0)
        result = wait_result(child);
    if (shell->interactive)
        signal(SIGINT, sh_interrupt);
    return result;
}
