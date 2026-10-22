NAME = libmy.a

SRC_DIR = lib/my
INCLUDE_DIR = include
TEST_DIR = tests
OBJ_DIR = obj

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
TEST_SRC = $(wildcard $(TEST_DIR)/*.c)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(INCLUDE_DIR)
CRITERION_FLAGS = -lcriterion

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

tests: $(NAME) test_run

test_run: $(TEST_SRC)
	$(CC) $(CFLAGS) -I$(TEST_DIR) $(TEST_SRC) $(NAME) $(CRITERION_FLAGS) -o $(TEST_DIR)/test_my
	@echo "Running tests..."
	@$(TEST_DIR)/test_my

clean:
	rm -rf $(OBJ_DIR) $(NAME) $(TEST_DIR)/test_my

fclean: clean
	rm -rf $(OBJ_DIR)

re: fclean all

.PHONY: all clean fclean re tests
