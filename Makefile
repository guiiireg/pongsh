NAME	=	pongsh

CC	=	gcc

CFLAGS	=	-Wall -Wextra -Werror -I./include

SRC	=	src/main.c \
		src/core/prompt.c \
		src/core/shell_loop.c \
		src/lib/is_empty_line.c \
		src/lib/free_word_array.c \
		src/parsing/split_words.c \
		src/execution/exec_command.c \
		src/builtins/builtin_exit.c

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
