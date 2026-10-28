CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -Iinclude

NAME    = libmy.a

SRC     = lib/my/my_putchar.c     \
          lib/my/my_putstr.c      \
          lib/my/my_puterr.c      \
          lib/my/my_isalpha.c     \
          lib/my/my_isdigit.c     \
          lib/my/my_isalnum.c     \
          lib/my/my_isupper.c     \
          lib/my/my_islower.c     \
          lib/my/my_isprint.c     \
          lib/my/my_isascii.c     \
          lib/my/my_toupper.c     \
          lib/my/my_tolower.c     \
          lib/my/my_strlen.c      \
          lib/my/my_strcpy.c      \
          lib/my/my_strncpy.c     \
          lib/my/my_strcat.c      \
          lib/my/my_strncat.c     \
          lib/my/my_strdup.c      \
          lib/my/my_strcmp.c      \
          lib/my/my_strncmp.c     \
          lib/my/my_strchr.c      \
          lib/my/my_strrchr.c     \
          lib/my/my_strstr.c      \
          lib/my/my_revstr.c      \
          lib/my/my_memset.c      \
          lib/my/my_bzero.c       \
          lib/my/my_memcpy.c      \
          lib/my/my_memmove.c     \
          lib/my/my_memchr.c      \
          lib/my/my_memcmp.c      \
          lib/my/my_calloc.c       \
          lib/my/my_str_to_word_array.c \
          lib/my/my_show_word_array.c   \
          lib/my/my_free_word_array.c   \
          lib/my/my_sort.c         \
          lib/my/my_sort_word_array.c

OBJ     = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) unit_tests

re: fclean all

tests_run: $(SRC) $(wildcard tests/test_*.c)
	gcc -Wall -Wextra -Werror -Iinclude $(SRC) $(wildcard tests/test_*.c) \
	    -lcriterion -o unit_tests
	./unit_tests

.PHONY: all clean fclean re tests_run
