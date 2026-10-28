CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -Iinclude

NAME    = libmy.a

SRC     = lib/my/io/my_putchar.c            \
          lib/my/io/my_putstr.c             \
          lib/my/io/my_puterr.c             \
          lib/my/ctype/my_isalpha.c         \
          lib/my/ctype/my_isdigit.c         \
          lib/my/ctype/my_isalnum.c          \
          lib/my/ctype/my_isupper.c         \
          lib/my/ctype/my_islower.c         \
          lib/my/ctype/my_isprint.c         \
          lib/my/ctype/my_isascii.c         \
          lib/my/ctype/my_toupper.c         \
          lib/my/ctype/my_tolower.c         \
          lib/my/string/my_strlen.c         \
          lib/my/string/my_strcpy.c         \
          lib/my/string/my_strncpy.c        \
          lib/my/string/my_strcat.c         \
          lib/my/string/my_strncat.c        \
          lib/my/string/my_strdup.c         \
          lib/my/string/my_strcmp.c         \
          lib/my/string/my_strncmp.c        \
          lib/my/string/my_strchr.c         \
          lib/my/string/my_strrchr.c        \
          lib/my/string/my_strstr.c         \
          lib/my/string/my_revstr.c         \
          lib/my/memory/my_memset.c         \
          lib/my/memory/my_bzero.c          \
          lib/my/memory/my_memcpy.c         \
          lib/my/memory/my_memmove.c        \
          lib/my/memory/my_memchr.c         \
          lib/my/memory/my_memcmp.c         \
          lib/my/memory/my_calloc.c         \
          lib/my/word_array/my_str_to_word_array.c \
          lib/my/word_array/my_show_word_array.c   \
          lib/my/word_array/my_free_word_array.c   \
          lib/my/word_array/my_sort.c       \
          lib/my/word_array/my_sort_word_array.c

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
