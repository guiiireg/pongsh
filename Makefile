##
## Makefile
##

CC	= gcc
AR	= ar
CFLAGS	= -Wall -Wextra -Werror -std=c99 -Iinclude -Isrc
ARFLAGS	= rc

BUILD		= build
OBJ_DIR		= $(BUILD)/obj

MY_SRC		= $(wildcard src/my/*.c)
MY_PRINTF_SRC	= $(wildcard src/my_printf/*.c)
TESTS_SRC	= $(wildcard tests/my/*.c) $(wildcard tests/my_printf/*.c)

MY_OBJ		= $(MY_SRC:src/%.c=$(OBJ_DIR)/%.o)
MY_PRINTF_OBJ	= $(MY_PRINTF_SRC:src/%.c=$(OBJ_DIR)/%.o)

LIBMY		= $(BUILD)/libmy.a
LIBMY_PRINTF	= $(BUILD)/libmy_printf.a
TESTS_BIN	= $(BUILD)/tests_libmy

all:		$(LIBMY) $(LIBMY_PRINTF)

$(LIBMY):	$(MY_OBJ)
		$(AR) $(ARFLAGS) $@ $^

$(LIBMY_PRINTF):	$(MY_PRINTF_OBJ)
		$(AR) $(ARFLAGS) $@ $^

$(OBJ_DIR)/%.o:	src/%.c
		mkdir -p $(dir $@)
		$(CC) $(CFLAGS) -c $< -o $@

tests_run:	re
		$(CC) $(CFLAGS) $(TESTS_SRC) -L$(BUILD) -lmy_printf -lmy -lcriterion -o $(TESTS_BIN)

clean:
		rm -rf $(BUILD)

fclean:		clean

re:		fclean
		+@"$(MAKE)" all

.PHONY:		all clean fclean re tests_run
