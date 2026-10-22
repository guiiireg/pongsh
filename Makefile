##
## Makefile
##

CC	= gcc
AR	= ar
CFLAGS	= -Wall -Wextra -Werror -std=c99
ARFLAGS	= rc

NAME	= libmy.a

SRC	= $(wildcard lib/my/*.c)
OBJ	= $(SRC:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
		$(AR) $(ARFLAGS) $@ $^

%.o:		%.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -f $(OBJ)

fclean:		clean
		rm -f $(NAME)

re:		fclean
		all

.PHONY:		all clean fclean re
