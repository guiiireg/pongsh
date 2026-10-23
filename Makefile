##
## Makefile
##

CC	= gcc
AR	= ar
CFLAGS	= -Wall -Wextra -Werror -std=c99
ARFLAGS	= rc

NAME	= libmy.a

SRC	= $(wildcard lib/my/*.c) $(wildcard lib/my_printf/*.c)
OBJ	= $(SRC:.c=.o)

TESTS_SRC	= $(wildcard tests/*.c) $(wildcard tests/my_printf/*.c)
TESTS_BIN	= tests_libmy

all:		$(NAME)

$(NAME):	$(OBJ)
		$(AR) $(ARFLAGS) $@ $^

%.o:		%.c
		$(CC) $(CFLAGS) -c $< -o $@

tests_run:	re
		$(CC) $(CFLAGS) $(TESTS_SRC) -L. -lmy -lcriterion -o $(TESTS_BIN)

clean:
		rm -f $(OBJ)

fclean:		clean
		rm -f $(NAME) $(TESTS_BIN)

re:		fclean
		+@"$(MAKE)" all

.PHONY:		all clean fclean re tests_run
