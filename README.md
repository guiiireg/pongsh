# PONGSH - A Simple C Shell

## Overview
PONGSH is a simple shell implemented in C, designed as a learning project to demonstrate basic shell functionality, custom command handling, and modular C programming. It features custom implementations of `ls` and `cd` commands, memory utilities, and a minimal command loop.

## Features
- Custom shell prompt (`pongsh$`)
- Built-in commands: `ls`, `ls -flags`, `cd`, `clear`, `exit`
- Custom `ls` implementation with support for flags (e.g., `-a`, `-l`)
- Custom `cd` implementation with home directory support (`~`) and error handling
- Modular codebase with custom string, memory, and I/O utilities
- Clean build system with Makefile

## Project Structure
```
├── src/
│   ├── main.c          # Main entry point
│   ├── shell.c         # Shell loop implementation
│   ├── input.c         # Input handling
│   └── command.c       # Command execution and parsing
├── lib/
│   ├── my_ls/          # Custom ls command implementation
│   ├── my_cd/          # Custom cd command implementation
│   ├── my_printf/      # Custom printf implementation
│   ├── my_io.c         # Basic I/O functions
│   ├── my_memory.c     # Memory management
│   ├── my_string.c     # String utilities
│   └── my_utils.c      # General utilities
├── include/
│   ├── pongsh.h        # Main project header
│   ├── my_ls.h         # ls command header
│   ├── my_cd.h         # cd command header
│   └── my_printf.h     # printf implementation header
├── build/
├── Makefile
└── .gitignore
```

## Key Functions
- `shell_loop()` - Main shell execution loop
- `read_input()` - Reads a line of input from the user
- `execute_command()` - Processes and executes shell commands
- `my_ls()` / `my_ls_with_flags()` - Custom `ls` command implementation
- `my_cd()` - Custom `cd` command with home directory and path resolution
- `my_printf()` - Custom printf for formatted output

## Building & Running
```sh
make
./build/bin/pongsh
```

## Usage
- Type `ls` or `ls -l`, `ls -a` to list files
- Type `cd [directory]` to change directories (supports `~` for home)
- Type `cd` (without arguments) to go to home directory
- Type `clear` to clear the terminal
- Type `exit` to quit the shell

## Recent Updates
- Added custom `cd` command implementation with full path resolution
- Refactored main.c into modular components (shell.c, input.c, command.c)
- Enhanced project structure with proper header organization
- Improved error handling and memory management
- Clean coding style with minimal comments and proper variable initialization

---
