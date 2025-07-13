# PONGSH - C Shell 💻

## Overview
PONGSH is a shell implemented in C with a colorful interface and essential built-in commands. It features a clean architecture and provides a pleasant user experience with Unicode characters and color-coded outputs.

## Features
### 🎨 Modern Interface
- Beautiful prompt with colors: `user@hostname ~/path`
- Welcome banner with Unicode characters and emojis
- Color-coded error messages and command feedback
- Emoji-enhanced status indicators (★ ✗ ➜ ⚡ 📁)

### 🛠️ Built-in Commands
- **File Operations**: `ls` (with flags -a, -l), `cat`, `pwd`
- **Navigation**: `cd` (with home directory support ~)
- **Utilities**: `echo`, `clear`, `exit`
- All commands feature modern error handling with colors

## Project Structure
```
├── src/
│   ├── main.c                    # Entry point
│   ├── shell.c                   # Shell main loop
│   ├── input.c                   # Input handling
│   ├── command.c                 # Command parsing & execution
│   └── prompt/
│       └── prompt_utils.c        # Prompt display utilities
├── lib/
│   ├── display/
│   │   └── color_display.c       # Welcome messages & banners
│   ├── utils/
│   │   └── path_utils.c          # Path manipulation utilities
│   ├── my_cat/
│   │   ├── my_cat.c              # Cat command core
│   │   └── cat_io.c              # Cat I/O operations
│   ├── my_ls/                    # Directory listing (8 files)
│   ├── my_cd/                    # Directory navigation (2 files)
│   ├── my_pwd/                   # Current directory display
│   ├── my_echo/                  # Text output
│   ├── my_printf/                # Custom printf implementation
│   ├── color_print.c             # Color printing functions
│   ├── color_utils.c             # Color utilities
│   ├── my_io.c                   # Basic I/O operations
│   ├── my_memory.c               # Memory management
│   ├── my_string.c               # String manipulation
│   └── my_utils.c                # General utilities
├── include/
│   ├── pongsh.h                  # Main project header
│   ├── colors.h                  # Color definitions & prototypes
│   ├── my_cat.h                  # Cat command header
│   ├── my_ls.h, my_cd.h, my_pwd.h, my_echo.h, my_printf.h
├── build/                        # Compiled objects & executables
├── Makefile                      # Build system
└── .gitignore
```

## Building & Running
```sh
make
./build/bin/pongsh
```

## Usage

### 📋 **Available Commands**
| Command | Description | Example |
|---------|-------------|---------|
| `ls` | List directory contents | `ls`, `ls -l`, `ls -a` |
| `cat` | Display file contents | `cat file.txt` |
| `cd` | Change directory | `cd /tmp`, `cd ~`, `cd` |
| `pwd` | Show current directory | `pwd` |
| `echo` | Display text | `echo "Hello World"` |
| `clear` | Clear screen with welcome | `clear` |
| `exit` | Quit with goodbye message | `exit` |

### 🎨 **Interface Preview**
The shell features a modern, colorful interface with:

**Welcome Screen:**
```
═══════════════════════════════════════════════════════════════════════════════
                              💻 PONGSH                        
═══════════════════════════════════════════════════════════════════════════════

★ Welcome back, user! Running on hostname ★

➜ Type commands to get started, or 'exit' to quit
⚡ Available commands: ls, cd, pwd, echo, cat, clear, exit
```

**Modern Prompt:**
```
user@hostname ~/project
user@hostname /tmp
user@hostname ~
```

**Color-Coded Output:**
- 🟢 **Success messages** with ★ symbols
- 🔴 **Error messages** with ✗ symbols  
- 🔵 **Info messages** with ➜ symbols
- 📁 **Directory paths** with folder icons
