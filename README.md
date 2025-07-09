# PONGSH - A Simple C Shell

## Overview
PONGSH is a simple shell implemented in C, designed as a learning project to demonstrate basic shell functionality and custom command handling. It features custom implementations of `ls` and `cd` commands, memory utilities, and a minimal command loop.

## Features
- Custom shell prompt (`pongsh$`)
- Built-in commands: `ls`, `ls -flags`, `cd`, `clear`, `exit`
- Custom `ls` implementation with support for flags (e.g., `-a`, `-l`)
- Custom `cd` implementation with home directory support (`~`) and error handling
- Custom string, memory, and I/O utilities
- Clean build system with Makefile

## Project Structure
```
├── src/
│   ├── main.c
│   ├── shell.c
│   ├── input.c
│   └── command.c
├── lib/
│   ├── my_ls/
│   ├── my_cd/
│   ├── my_printf/
│   ├── my_io.c
│   ├── my_memory.c
│   ├── my_string.c
│   └── my_utils.c
├── include/
│   ├── pongsh.h
│   ├── my_ls.h
│   ├── my_cd.h
│   └── my_printf.h
├── build/
├── Makefile
└── .gitignore
```

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

---
