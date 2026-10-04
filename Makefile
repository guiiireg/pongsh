NAME	=	pongsh

CC	=	gcc

CFLAGS	=	-Wall -Wextra -Werror -I./include

SRC	=	src/main.c

OBJ	=	$(SRC:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

tests_run:
	@echo "No tests configured yet"

.PHONY:	all clean fclean re tests_run
