NAME	=	pongsh

TEST_NAME	=	unit_tests

CC	=	gcc

CFLAGS	=	-Wall -Wextra -Werror -I./include

SRC	=	src/main.c \
		src/core/prompt.c \
		src/core/shell_loop.c \
		src/lib/is_empty_line.c \
		src/lib/free_word_array.c \
		src/parsing/split_words.c \
		src/execution/exec_command.c \
		src/builtins/builtin_exit.c \
		src/builtins/builtin_cd.c

TEST_SRC	=	src/core/prompt.c \
			src/core/shell_loop.c \
			src/lib/is_empty_line.c \
			src/lib/free_word_array.c \
			src/parsing/split_words.c \
			src/execution/exec_command.c \
			src/builtins/builtin_exit.c \
			src/builtins/builtin_cd.c \
			tests/test_is_empty_line.c \
			tests/test_split_words.c \
			tests/test_builtins.c \
			tests/test_builtin_cd.c

OBJ	=	$(SRC:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

$(TEST_NAME):	$(TEST_SRC)
	$(CC) -o $(TEST_NAME) $(TEST_SRC) $(CFLAGS) -lcriterion

tests_run:	$(TEST_NAME)
	./$(TEST_NAME)
	valgrind --leak-check=full --error-exitcode=1 ./$(TEST_NAME)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)
	rm -f $(TEST_NAME)

re:	fclean all

.PHONY:	all clean fclean re tests_run
