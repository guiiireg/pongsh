// ============================
//           PONGSH
// ============================
// Made by Guireg on 17/08/2025
// Last update: 17/08/2025
// ============================
#include "../include/pongsh.h"

int main(void)
{
    return pongsh_main();
}

int pongsh_main(void)
{
    my_printf("Welcome to pongsh - A simple shell\n");
    my_printf("Type 'help' for available commands\n\n");
    return shell_loop();
}
