NAME := libmy.a
PRINTF_DIR := ../my_printf
SRC := $(sort $(wildcard my_*.c $(PRINTF_DIR)/my_*.c))
OBJ := $(notdir $(SRC:.c=.o))
HEADERS := $(wildcard ../../include/*.h)

vpath %.c $(PRINTF_DIR)

CPPFLAGS += -I../../include
CFLAGS += -std=c11 -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJ) Makefile
	$(AR) rcs $@ $(OBJ)

$(OBJ): $(HEADERS)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -ffreestanding -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re
