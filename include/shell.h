#ifndef SHELL_H_
    #define SHELL_H_

    #include <unistd.h>
    #include <stdlib.h>
    #include <stdio.h>

    #define SUCCESS 0
    #define FAILURE 84

void display_prompt(void);
int shell_loop(void);

#endif /* !SHELL_H_ */
