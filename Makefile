# =============================================================================
# PROJECT CONFIGURATION
# =============================================================================
# Core project settings - modify these for your specific project
PROJECT_NAME    := pongsh
PROJECT_FULL    := PONGSH C Project
VERSION         := 1.0.0
AUTHOR          := Development Team
DESCRIPTION     := A comprehensive C project demonstration with custom \
				   libraries
LICENSE         := MIT

# Build configuration options
BUILD_TYPE      ?= debug
STANDARD        := c99

# =============================================================================
# TERMINAL COLORS AND FORMATTING
# =============================================================================
# ANSI color codes for beautiful terminal output
RED     := \033[0;31m
GREEN   := \033[0;32m
YELLOW  := \033[0;33m
BLUE    := \033[0;34m
PURPLE  := \033[0;35m
CYAN    := \033[0;36m
WHITE   := \033[0;37m
BOLD    := \033[1m
DIM     := \033[2m
RESET   := \033[0m

# Status indicators
SUCCESS := $(GREEN)✓$(RESET)
ERROR   := $(RED)✗$(RESET)
INFO    := $(BLUE)ℹ$(RESET)
WARN    := $(YELLOW)⚠$(RESET)
BUILD   := $(PURPLE)⚡$(RESET)

# =============================================================================
# COMPILER AND TOOLS CONFIGURATION
# =============================================================================
# Primary toolchain
CC       := gcc
AR       := ar
RANLIB   := ranlib
STRIP    := strip
MKDIR    := mkdir -p
RM       := rm -rf

# Build type specific flags
ifeq ($(BUILD_TYPE),debug)
	CFLAGS := -Wall -Wextra -Werror -std=$(STANDARD) -g -DDEBUG -O0
	LDFLAGS := -g
else ifeq ($(BUILD_TYPE),release)
	CFLAGS := -Wall -Wextra -Werror -std=$(STANDARD) -O2 -DNDEBUG
	LDFLAGS := -s
else
	$(error Invalid BUILD_TYPE: $(BUILD_TYPE). Use 'debug' or 'release')
endif

ARFLAGS  := rcs
LDLIBS   := -lm

# =============================================================================
# DIRECTORY STRUCTURE
# =============================================================================
# Project directory layout
SRC_DIR     := src
LIB_DIR     := lib
INC_DIR     := include
BUILD_DIR   := build
OBJ_DIR     := $(BUILD_DIR)/obj
BIN_DIR     := $(BUILD_DIR)/bin
DOC_DIR     := docs
DIST_DIR    := dist

# =============================================================================
# SOURCE FILES AND DEPENDENCIES
# =============================================================================
# Automatic source file discovery
MAIN_SRC := $(SRC_DIR)/main.c
LIB_SRCS := $(wildcard $(LIB_DIR)/*.c) \
			$(wildcard $(LIB_DIR)/my_printf/*.c) \
			$(wildcard $(LIB_DIR)/my_ls/*.c)
HEADERS  := $(wildcard $(INC_DIR)/*.h)

# Object file generation
MAIN_OBJ := $(OBJ_DIR)/main.o
LIB_OBJS := $(patsubst $(LIB_DIR)/%.c,$(OBJ_DIR)/%.o,$(LIB_SRCS))
ALL_OBJS := $(MAIN_OBJ) $(LIB_OBJS)

# Dependency files
DEPS := $(ALL_OBJS:.o=.d)

# Output targets
EXECUTABLE := $(BIN_DIR)/$(PROJECT_NAME)
STATIC_LIB := $(BUILD_DIR)/lib$(PROJECT_NAME).a

# =============================================================================
# MAIN BUILD RULES
# =============================================================================

# Default target
.DEFAULT_GOAL := all

all: banner create_dirs $(EXECUTABLE)
	@echo ""
	@echo "$(SUCCESS) $(BOLD)Build completed successfully!$(RESET)"

# Create the main executable
$(EXECUTABLE): $(ALL_OBJS) | $(BIN_DIR)
	@echo "$(BUILD) $(CYAN)[LINKING]$(RESET) Creating executable \
$(BOLD)$(PROJECT_NAME)$(RESET)"
	@$(CC) $(LDFLAGS) $(ALL_OBJS) -o $@ $(LDLIBS)
	@echo "$(SUCCESS) Executable created: $(BOLD)$@$(RESET)"

# Create static library
$(STATIC_LIB): $(LIB_OBJS) | $(BUILD_DIR)
	@echo "$(BUILD) $(CYAN)[ARCHIVE]$(RESET) Creating static library"
	@$(AR) $(ARFLAGS) $@ $(LIB_OBJS)
	@$(RANLIB) $@
	@echo "$(SUCCESS) Static library created: $(BOLD)$@$(RESET)"

# =============================================================================
# COMPILATION RULES
# =============================================================================

# Compile main source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(BUILD) $(YELLOW)[COMPILE]$(RESET) $< → $@"
	@$(CC) -I$(INC_DIR) $(CFLAGS) -MMD -MP -c $< -o $@

# Compile library source files
$(OBJ_DIR)/%.o: $(LIB_DIR)/%.c | $(OBJ_DIR)
	@echo "$(BUILD) $(YELLOW)[COMPILE]$(RESET) $< → $@"
	@$(MKDIR) $(dir $@)
	@$(CC) -I$(INC_DIR) $(CFLAGS) -MMD -MP -c $< -o $@

# =============================================================================
# DIRECTORY CREATION
# =============================================================================

# Create necessary directories
create_dirs: $(OBJ_DIR) $(BIN_DIR) $(BUILD_DIR)

$(OBJ_DIR) $(BIN_DIR) $(BUILD_DIR) $(DOC_DIR) $(DIST_DIR):
	@echo "$(INFO) $(BLUE)[MKDIR]$(RESET) Creating directory $@"
	@$(MKDIR) $@

# =============================================================================
# CLEANING OPERATIONS
# =============================================================================

# Clean object files and dependencies
clean: banner
	@echo "$(WARN) $(RED)[CLEAN]$(RESET) Removing object files and \
dependencies"
	@$(RM) $(OBJ_DIR) $(BUILD_DIR)/*.d
	@echo "$(SUCCESS) Object files cleaned"

# Full clean - remove all generated files
fclean: banner clean
	@echo "$(WARN) $(RED)[FCLEAN]$(RESET) Removing all generated files"
	@$(RM) $(BUILD_DIR) $(DIST_DIR)
	@echo "$(SUCCESS) All generated files removed"

# Clean and rebuild everything
re: fclean all

# =============================================================================
# EXECUTION AND TESTING
# =============================================================================

# Run the program
run: $(EXECUTABLE)
	@echo "$(SUCCESS) $(GREEN)[RUN]$(RESET) Executing \
$(BOLD)$(PROJECT_NAME)$(RESET)"
	@echo "$(DIM)==================================================\
============$(RESET)"
	@./$(EXECUTABLE) $(ARGS)
	@echo "$(DIM)==================================================\
============$(RESET)"

# Debug with GDB
debug: $(EXECUTABLE)
	@echo "$(INFO) $(PURPLE)[DEBUG]$(RESET) Starting GDB debugger"
	@gdb ./$(EXECUTABLE)

# Memory analysis with Valgrind
valgrind: $(EXECUTABLE)
	@echo "$(INFO) $(PURPLE)[VALGRIND]$(RESET) Running memory analysis"
	@valgrind --leak-check=full --show-leak-kinds=all \
	--track-origins=yes ./$(EXECUTABLE)

# =============================================================================
# DEVELOPMENT TOOLS
# =============================================================================

# Static code analysis
check: banner
	@echo "$(INFO) $(CYAN)[ANALYSIS]$(RESET) Running static code analysis"
ifneq ($(shell which cppcheck),)
	@cppcheck --enable=all --suppress=missingIncludeSystem \
	$(SRC_DIR) $(LIB_DIR)
else
	@echo "$(WARN) cppcheck not found, skipping analysis"
endif
	@echo "$(SUCCESS) Analysis complete"

# Code formatting
format: banner
	@echo "$(INFO) $(BLUE)[FORMAT]$(RESET) Formatting source code"
ifneq ($(shell which clang-format),)
	@find $(SRC_DIR) $(LIB_DIR) $(INC_DIR) -name "*.c" -o -name "*.h" | \
	 xargs clang-format -i --style="{BasedOnStyle: GNU, IndentWidth: 4}"
	@echo "$(SUCCESS) Code formatting complete"
else
	@echo "$(WARN) clang-format not found, skipping formatting"
endif

# =============================================================================
# INSTALLATION AND PACKAGING
# =============================================================================

# Install to system
install: $(EXECUTABLE) banner
	@echo "$(INFO) $(GREEN)[INSTALL]$(RESET) Installing $(PROJECT_NAME) \
to system"
	@sudo cp $(EXECUTABLE) /usr/local/bin/
	@echo "$(SUCCESS) Installation complete"

# Uninstall from system
uninstall: banner
	@echo "$(WARN) $(RED)[UNINSTALL]$(RESET) Removing $(PROJECT_NAME) \
from system"
	@sudo rm -f /usr/local/bin/$(PROJECT_NAME)
	@echo "$(SUCCESS) Uninstallation complete"

# Create distribution tarball
dist: fclean banner | $(DIST_DIR)
	@echo "$(INFO) $(CYAN)[PACKAGE]$(RESET) Creating distribution tarball"
	@tar --exclude='.git' --exclude='*.tar.gz' \
	-czf $(DIST_DIR)/$(PROJECT_NAME)-$(VERSION).tar.gz .
	@echo "$(SUCCESS) Distribution created: \
$(BOLD)$(DIST_DIR)/$(PROJECT_NAME)-$(VERSION).tar.gz$(RESET)"

# =============================================================================
# INFORMATION AND HELP SYSTEM
# =============================================================================

# Project information display
info: banner
	@echo "$(BOLD)Project Information:$(RESET)"
	@echo "$(DIM)=====================================================\
==============================$(RESET)"
	@echo "  $(CYAN)Name:$(RESET)         $(BOLD)$(PROJECT_FULL)$(RESET)"
	@echo "  $(CYAN)Version:$(RESET)      $(BOLD)$(VERSION)$(RESET)"
	@echo "  $(CYAN)Author:$(RESET)       $(BOLD)$(AUTHOR)$(RESET)"
	@echo "  $(CYAN)License:$(RESET)      $(BOLD)$(LICENSE)$(RESET)"
	@echo "  $(CYAN)Description:$(RESET)  $(DESCRIPTION)"
	@echo ""
	@echo "$(BOLD)Build Configuration:$(RESET)"
	@echo "$(DIM)=====================================================\
==============================$(RESET)"
	@echo "  $(CYAN)Compiler:$(RESET)     $(BOLD)$(CC)$(RESET)"
	@echo "  $(CYAN)Build Type:$(RESET)   $(BOLD)$(BUILD_TYPE)$(RESET)"
	@echo "  $(CYAN)Standard:$(RESET)     $(BOLD)$(STANDARD)$(RESET)"
	@echo "  $(CYAN)CFLAGS:$(RESET)       $(YELLOW)$(CFLAGS)$(RESET)"
	@echo ""
	@echo "$(BOLD)Source Files:$(RESET)"
	@echo "$(DIM)=====================================================\
==============================$(RESET)"
	@echo "  $(CYAN)Main files:$(RESET)   $(BOLD)$(words $(MAIN_SRC))$(RESET)"
	@echo "  $(CYAN)Library files:$(RESET) \
$(BOLD)$(words $(LIB_SRCS))$(RESET)"
	@echo "  $(CYAN)Header files:$(RESET) $(BOLD)$(words $(HEADERS))$(RESET)"

# Comprehensive help system
help: banner
	@echo "$(BOLD)Available Commands:$(RESET)"
	@echo "$(DIM)=====================================================\
==============================$(RESET)"
	@echo ""
	@echo "$(BOLD)$(GREEN)Building:$(RESET)"
	@echo "  $(CYAN)make$(RESET) or $(CYAN)make all$(RESET)     Build the \
complete project"
	@echo "  $(CYAN)make static$(RESET)           Build static library only"
	@echo "  $(CYAN)make clean$(RESET)            Remove object files"
	@echo "  $(CYAN)make fclean$(RESET)           Remove all generated files"
	@echo "  $(CYAN)make re$(RESET)               Clean and rebuild \
everything"
	@echo ""
	@echo "$(BOLD)$(GREEN)Execution & Testing:$(RESET)"
	@echo "  $(CYAN)make run$(RESET)              Run the program"
	@echo "  $(CYAN)make run ARGS=\"...\"$(RESET)    Run with arguments"
	@echo "  $(CYAN)make debug$(RESET)            Debug with GDB"
	@echo "  $(CYAN)make valgrind$(RESET)         Memory analysis with \
Valgrind"
	@echo ""
	@echo "$(BOLD)$(GREEN)Development Tools:$(RESET)"
	@echo "  $(CYAN)make check$(RESET)            Static code analysis"
	@echo "  $(CYAN)make format$(RESET)           Format source code"
	@echo ""
	@echo "$(BOLD)$(GREEN)Installation & Distribution:$(RESET)"
	@echo "  $(CYAN)make install$(RESET)          Install to system"
	@echo "  $(CYAN)make uninstall$(RESET)        Remove from system"
	@echo "  $(CYAN)make dist$(RESET)             Create distribution \
tarball"
	@echo ""
	@echo "$(BOLD)$(GREEN)Information:$(RESET)"
	@echo "  $(CYAN)make info$(RESET)             Show project information"
	@echo "  $(CYAN)make help$(RESET)             Show this help message"
	@echo "  $(CYAN)make man$(RESET)              Show manual page"
	@echo ""
	@echo "$(BOLD)$(GREEN)Build Configuration:$(RESET)"
	@echo "  $(CYAN)make BUILD_TYPE=debug$(RESET)   Build with debug info"
	@echo "  $(CYAN)make BUILD_TYPE=release$(RESET) Build optimized version"

# Manual page
man: banner
	@echo "$(BOLD)$(PROJECT_NAME)(1)$(RESET)                    User \
Commands                    $(BOLD)$(PROJECT_NAME)(1)$(RESET)"
	@echo ""
	@echo "$(BOLD)NAME$(RESET)"
	@echo "       $(PROJECT_NAME) - $(DESCRIPTION)"
	@echo ""
	@echo "$(BOLD)SYNOPSIS$(RESET)"
	@echo "       $(CYAN)$(PROJECT_NAME)$(RESET) [$(YELLOW)options$(RESET)] \
[$(YELLOW)arguments$(RESET)]"
	@echo ""
	@echo "$(BOLD)DESCRIPTION$(RESET)"
	@echo "       $(PROJECT_FULL) is a comprehensive C project that \
demonstrates"
	@echo "       modern C programming techniques with a well-structured \
build system."
	@echo ""
	@echo "$(BOLD)PROJECT STRUCTURE$(RESET)"
	@echo "       $(CYAN)$(SRC_DIR)/$(RESET)     Main source files"
	@echo "       $(CYAN)$(LIB_DIR)/$(RESET)     Library implementation files"
	@echo "       $(CYAN)$(INC_DIR)/$(RESET)     Header files"
	@echo "       $(CYAN)$(BUILD_DIR)/$(RESET)   Generated build files"
	@echo ""
	@echo "$(BOLD)BUILDING$(RESET)"
	@echo "       To build the project:"
	@echo "           $(CYAN)make$(RESET)"
	@echo ""
	@echo "$(BOLD)AUTHOR$(RESET)"
	@echo "       $(AUTHOR)"

# Display project banner
banner:
	@echo ""
	@echo "$(BOLD)$(CYAN)#====================================\
=========================================#$(RESET)"
	@echo "$(BOLD)$(CYAN)#                            \
$(WHITE)$(PROJECT_FULL)$(CYAN)                                 #$(RESET)"
	@echo "$(BOLD)$(CYAN)#                          \
$(YELLOW)Version $(VERSION) - $(BUILD_TYPE)$(CYAN)                            \
  #$(RESET)"
	@echo "$(BOLD)$(CYAN)#====================================\
=========================================#$(RESET)"
	@echo ""

# Build static library
static: $(STATIC_LIB)

# =============================================================================
# DEPENDENCY MANAGEMENT
# =============================================================================

# Include dependency files if they exist
-include $(DEPS)

# =============================================================================
# SPECIAL TARGETS
# =============================================================================

# Declare phony targets
.PHONY: all clean fclean re run debug valgrind check format install \
		uninstall dist info help man banner create_dirs static

# Delete intermediate files on error
.DELETE_ON_ERROR:

# =============================================================================
# END OF MAKEFILE
# =============================================================================
