#include "../../include/shell.h"

static void run_child(char **argv)
{
    execvp(argv[0], argv);
    perror(argv[0]);
    exit(127);
}

static int wait_child(pid_t pid)
{
    int status = 0;

    if (waitpid(pid, &status, 0) == -1)
        return (FAILURE);
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    if (WIFSIGNALED(status))
        return (128 + WTERMSIG(status));
    return (status);
}

int exec_command(char **argv)
{
    pid_t pid = 0;

    if (argv == NULL || argv[0] == NULL)
        return (SUCCESS);
    pid = fork();
    if (pid == -1) {
        perror("fork");
        return (FAILURE);
    }
    if (pid == 0)
        run_child(argv);
    return (wait_child(pid));
}
