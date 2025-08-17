// ============================
//          HISTORY
// ============================
// Made by Guireg on 17/08/2025
// Last update: 17/08/2025
// ============================
#include "../../include/pongsh.h"

static char *history[MAX_HISTORY];
static int history_count = 0;
static int history_start = 0;

void init_history(void)
{
    int i;

    for (i = 0; i < MAX_HISTORY; i++) {
        history[i] = NULL;
    }
    history_count = 0;
    history_start = 0;
}

void add_to_history(char const *command)
{
    char *cmd_copy;
    int cmd_len;
    int i;
    int insert_pos;

    if (command == NULL || my_strlen(command) == 0) {
        return;
    }
    cmd_len = my_strlen(command);
    cmd_copy = malloc((cmd_len + 1) * sizeof(char));
    if (!cmd_copy) {
        return;
    }
    for (i = 0; i < cmd_len; i++) {
        cmd_copy[i] = command[i];
    }
    cmd_copy[cmd_len] = '\0';
    if (history_count < MAX_HISTORY) {
        history[history_count] = cmd_copy;
        history_count++;
    } else {
        insert_pos = history_start;
        if (history[insert_pos] != NULL) {
            free(history[insert_pos]);
        }
        history[insert_pos] = cmd_copy;
        history_start = (history_start + 1) % MAX_HISTORY;
    }
}

void cleanup_history(void)
{
    int i;

    for (i = 0; i < MAX_HISTORY; i++) {
        if (history[i] != NULL) {
            free(history[i]);
            history[i] = NULL;
        }
    }
    history_count = 0;
    history_start = 0;
}

int pongsh_history(char **args)
{
    int i;
    int index;
    int num_to_show = history_count;

    (void)args;
    if (history_count == 0) {
        my_printf("No commands in history\n");
        return 1;
    }
    for (i = 0; i < num_to_show; i++) {
        if (history_count < MAX_HISTORY) {
            index = i;
        } else {
            index = (history_start + i) % MAX_HISTORY;
        }
        my_printf("%d  %s\n", i + 1, history[index]);
    }
    return 1;
}
