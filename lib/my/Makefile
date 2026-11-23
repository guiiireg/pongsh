NAME := libmy.a
SRC := $(sort $(wildcard my_*.c))
OBJ := $(SRC:.c=.o)

CPPFLAGS += -I../../include
CFLAGS += -std=c11 -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJ) Makefile
	$(AR) rcs $@ $(OBJ)

$(OBJ): ../../include/my.h

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re
