# PONGSH - A Simple C Shell

## Overview
PONGSH is a simple shell implemented in C, designed as a learning project to demonstrate basic shell functionality and custom command handling. It features custom implementations of `ls` and `cd` commands, memory utilities, and a minimal command loop.

## Features
- Custom shell prompt with current directory (`pongsh:/current/path$`)
- Built-in commands: `ls`, `ls -flags`, `cd`, `pwd`, `echo`, `clear`, `exit`
- Custom `ls` implementation with clean column display, colored directories, and support for flags (e.g., `-a`, `-l`)
- Custom `cd` implementation with home directory support (`~`) and error handling
- Custom `pwd` implementation to display current directory path
- Custom `echo` implementation to display text output
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
│   ├── my_pwd/
│   ├── my_echo/
│   ├── my_printf/
│   ├── my_io.c
│   ├── my_memory.c
│   ├── my_string.c
│   └── my_utils.c
├── include/
│   ├── pongsh.h
│   ├── my_ls.h
│   ├── my_cd.h
│   ├── my_pwd.h
│   ├── my_echo.h
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
- Type `pwd` to display the current directory path
- Type `echo [text]` to display text output
- Type `clear` to clear the terminal
- Type `exit` to quit the shell

The shell prompt automatically displays the current working directory:
```
pongsh:/home/user/project$ cd /tmp
pongsh:/tmp$ cd
pongsh:/home/user$ 
```

The `ls` command displays directories in blue color for better visual distinction:
- **Files**: Normal text color
- **Directories**: Blue color (both in normal and detailed `-l` mode)

---
