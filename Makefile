# ============================
#           MAKEFILE
# ============================
# Made by Guireg on 17/08/2025
# Last update: 17/08/2025
# ============================

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar
ARFLAGS = rcs

# Directories
LIB_DIR = lib
MY_DIR = $(LIB_DIR)/my
PRINTF_DIR = $(LIB_DIR)/my_printf
SRC_DIR = src
OBJ_DIR = obj
LIB_OBJ_DIR = $(OBJ_DIR)/lib
SRC_OBJ_DIR = $(OBJ_DIR)/src
INCLUDE_DIR = include

# Target names
LIB_NAME = libmy.a
SHELL_NAME = pongsh

# Source files
MY_SRCS = $(wildcard $(MY_DIR)/*.c)
PRINTF_SRCS = $(wildcard $(PRINTF_DIR)/*.c)
LIB_SRCS = $(MY_SRCS) $(PRINTF_SRCS)
SHELL_SRCS = $(wildcard $(SRC_DIR)/core/*.c) $(wildcard $(SRC_DIR)/builtins/*.c) $(wildcard $(SRC_DIR)/input/*.c)

# Object files
MY_OBJS = $(MY_SRCS:$(MY_DIR)/%.c=$(LIB_OBJ_DIR)/%.o)
PRINTF_OBJS = $(PRINTF_SRCS:$(PRINTF_DIR)/%.c=$(LIB_OBJ_DIR)/%.o)
LIB_OBJS = $(MY_OBJS) $(PRINTF_OBJS)
CORE_OBJS = $(wildcard $(SRC_DIR)/core/*.c)
BUILTINS_OBJS = $(wildcard $(SRC_DIR)/builtins/*.c)
INPUT_OBJS = $(wildcard $(SRC_DIR)/input/*.c)
SHELL_OBJS = $(CORE_OBJS:$(SRC_DIR)/%.c=$(SRC_OBJ_DIR)/%.o) $(BUILTINS_OBJS:$(SRC_DIR)/%.c=$(SRC_OBJ_DIR)/%.o) $(INPUT_OBJS:$(SRC_DIR)/%.c=$(SRC_OBJ_DIR)/%.o)

# Default target
all: $(SHELL_NAME)

# Create shell executable
$(SHELL_NAME): $(LIB_NAME) $(SHELL_OBJS)
	$(CC) $(CFLAGS) -o $@ $(SHELL_OBJS) -L. -lmy

# Create library (only printf and core functions)
$(LIB_NAME): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $^

# Create object directories
$(LIB_OBJ_DIR):
	mkdir -p $(LIB_OBJ_DIR)

$(SRC_OBJ_DIR):
	mkdir -p $(SRC_OBJ_DIR)/core $(SRC_OBJ_DIR)/builtins $(SRC_OBJ_DIR)/input

# Compile my/ sources
$(LIB_OBJ_DIR)/%.o: $(MY_DIR)/%.c | $(LIB_OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Compile my_printf/ sources
$(LIB_OBJ_DIR)/%.o: $(PRINTF_DIR)/%.c | $(LIB_OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Compile src/ sources
$(SRC_OBJ_DIR)/core/%.o: $(SRC_DIR)/core/%.c | $(SRC_OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(SRC_OBJ_DIR)/builtins/%.o: $(SRC_DIR)/builtins/%.c | $(SRC_OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(SRC_OBJ_DIR)/input/%.o: $(SRC_DIR)/input/%.c | $(SRC_OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Clean targets
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(LIB_NAME) $(SHELL_NAME)

re: fclean all

# Show library contents
show:
	@echo "Library contents:"
	@ar -t $(LIB_NAME) 2>/dev/null || echo "Library not built yet"

# Debug info
debug:
	@echo "MY_SRCS: $(MY_SRCS)"
	@echo "PRINTF_SRCS: $(PRINTF_SRCS)"
	@echo "SHELL_SRCS: $(SHELL_SRCS)"
	@echo "LIB_OBJS: $(LIB_OBJS)"
	@echo "SHELL_OBJS: $(SHELL_OBJS)"

# Build only library
lib: $(LIB_NAME)

.PHONY: all clean fclean re show debug lib
