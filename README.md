# PONGSH - A Simple C Shell

## Overview
PONGSH is a simple shell implemented in C, designed as a learning project to demonstrate basic shell functionality, custom command handling, and modular C programming. It features a custom implementation of the `ls` command, memory utilities, and a minimal command loop.

## Features
- Custom shell prompt (`pongsh$`)
- Built-in commands: `ls`, `ls -flags`, `clear`, `exit`
- Custom `ls` implementation with support for flags (e.g., `-a`, `-l`)
- Modular codebase with custom string, memory, and I/O utilities
- Clean build system with Makefile

## Project Structure
```
├── src/
├── lib/
│   ├── my_ls/
│   └── my_printf/
├── include/
├── build/
├── Makefile
└── .gitignore
```

## Key Functions
- `read_input()` - Reads a line of input from the user
- `execute_command()` - Processes and executes shell commands
- `my_ls()` / `my_ls_with_flags()` - Custom `ls` command implementation
- `my_printf()` - Custom printf for formatted output

## Building & Running
```sh
make
./build/bin/pongsh
```

## Usage
- Type `ls` or `ls -l`, `ls -a` to list files
- Type `clear` to clear the terminal
- Type `exit` to quit the shell

---
