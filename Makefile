##
## EPITECH PROJECT, 2026
## pongsh
## File description:
## Makefile for libmy and Criterion tests
##

SHELL       := /bin/bash

# Compilateur et archiveur
CC          ?= gcc
AR          ?= ar
ARFLAGS     := rcs

# Options de compilation
CFLAGS      := -Wall -Wextra -Werror
CPPFLAGS    := -Iinclude
TEST_FLAGS  := -lcriterion

# Cibles
NAME        := libmy.a
TEST_BIN    := unit_tests

# Répertoires
LIB_DIR     := lib/my
PRINTF_DIR  := lib/my_printf
TESTS_DIR   := tests
OBJ_DIR     := obj
LIB_OBJ_DIR := $(OBJ_DIR)/lib/my
PRINTF_OBJ_DIR := $(OBJ_DIR)/lib/my_printf
TEST_OBJ_DIR:= $(OBJ_DIR)/tests

# Fichiers sources et objets
SRCS        := $(sort $(wildcard $(LIB_DIR)/*.c))
PRINTF_SRCS := $(sort $(wildcard $(PRINTF_DIR)/*.c))
ALL_SRCS    := $(SRCS) $(PRINTF_SRCS)

OBJS        := $(SRCS:$(LIB_DIR)/%.c=$(LIB_OBJ_DIR)/%.o)
PRINTF_OBJS := $(PRINTF_SRCS:$(PRINTF_DIR)/%.c=$(PRINTF_OBJ_DIR)/%.o)
ALL_OBJS    := $(OBJS) $(PRINTF_OBJS)

TEST_SRCS   := $(sort $(wildcard $(TESTS_DIR)/*.c))
TEST_OBJS   := $(TEST_SRCS:$(TESTS_DIR)/%.c=$(TEST_OBJ_DIR)/%.o)

# Couleurs ANSI
C_RESET     := \033[0m
C_BOLD      := \033[1m
C_GREEN     := \033[1;32m
C_YELLOW    := \033[1;33m
C_BLUE      := \033[1;34m
C_CYAN      := \033[1;36m
C_MAGENTA   := \033[1;35m

# Règle par défaut
all: $(NAME)

# Règle de création de la bibliothèque statique
$(NAME): $(ALL_OBJS)
	@rm -f $(OBJ_DIR)/.lib_header_printed $(OBJ_DIR)/.printf_header_printed
	@printf "$(C_BLUE)[📦]$(C_RESET) Création de l'archive $(C_BOLD)$@$(C_RESET)...\r"
	@$(AR) $(ARFLAGS) $@ $(ALL_OBJS)
	@printf "\r\033[K$(C_GREEN)[✔]$(C_RESET) Bibliothèque $(C_BOLD)$@$(C_RESET) créée avec succès !\n"

# Compilation des objets de libmy
$(LIB_OBJ_DIR)/%.o: $(LIB_DIR)/%.c | $(LIB_OBJ_DIR)
	@if [ ! -f $(OBJ_DIR)/.lib_header_printed ]; then \
		touch $(OBJ_DIR)/.lib_header_printed; \
		printf "$(C_CYAN)[📁] Dossier: $(LIB_DIR)/$(C_RESET)\n"; \
	fi
	@printf "$(C_YELLOW)  [⏳]$(C_RESET) %s\r" "$<"
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	@printf "\r\033[K$(C_GREEN)  [✔]$(C_RESET) %s\n" "$<"

# Compilation des objets de lib/my_printf
$(PRINTF_OBJ_DIR)/%.o: $(PRINTF_DIR)/%.c | $(PRINTF_OBJ_DIR)
	@if [ ! -f $(OBJ_DIR)/.printf_header_printed ]; then \
		touch $(OBJ_DIR)/.printf_header_printed; \
		printf "$(C_CYAN)[📁] Dossier: $(PRINTF_DIR)/$(C_RESET)\n"; \
	fi
	@printf "$(C_YELLOW)  [⏳]$(C_RESET) %s\r" "$<"
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	@printf "\r\033[K$(C_GREEN)  [✔]$(C_RESET) %s\n" "$<"

# Règle pour compiler les tests unitaires
$(TEST_BIN): $(NAME) $(TEST_OBJS)
	@rm -f $(OBJ_DIR)/.tests_header_printed
	@printf "$(C_BLUE)[🔗]$(C_RESET) Édition des liens pour $(C_BOLD)$@$(C_RESET)...\r"
	@$(CC) -o $@ $(TEST_OBJS) -L. -lmy $(TEST_FLAGS)
	@printf "\r\033[K$(C_GREEN)[✔]$(C_RESET) Exécutable $(C_BOLD)$@$(C_RESET) généré avec succès !\n"

# Compilation des objets de tests
$(TEST_OBJ_DIR)/%.o: $(TESTS_DIR)/%.c | $(TEST_OBJ_DIR)
	@if [ ! -f $(OBJ_DIR)/.tests_header_printed ]; then \
		touch $(OBJ_DIR)/.tests_header_printed; \
		printf "$(C_CYAN)[📁] Dossier: $(TESTS_DIR)/$(C_RESET)\n"; \
	fi
	@printf "$(C_YELLOW)  [⏳]$(C_RESET) %s\r" "$<"
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	@printf "\r\033[K$(C_GREEN)  [✔]$(C_RESET) %s\n" "$<"

# Exécution des tests unitaires
tests_run: $(TEST_BIN)
	@printf "$(C_MAGENTA)[🚀] Lancement de la suite de tests Criterion...$(C_RESET)\n"
	@./$(TEST_BIN)

# Création des dossiers d'objets
$(LIB_OBJ_DIR):
	@mkdir -p $@

$(PRINTF_OBJ_DIR):
	@mkdir -p $@

$(TEST_OBJ_DIR):
	@mkdir -p $@

# Nettoyage
clean:
	@printf "$(C_YELLOW)[🧹]$(C_RESET) Nettoyage des fichiers objets...\r"
	@rm -rf $(OBJ_DIR)
	@printf "\r\033[K$(C_GREEN)[✔]$(C_RESET) Fichiers objets supprimés.\n"

fclean: clean
	@printf "$(C_YELLOW)[🧹]$(C_RESET) Nettoyage des exécutables et archives...\r"
	@rm -f $(NAME) $(TEST_BIN)
	@printf "\r\033[K$(C_GREEN)[✔]$(C_RESET) Nettoyage complet terminé.\n"

re: fclean all

.PHONY: all tests_run clean fclean re
