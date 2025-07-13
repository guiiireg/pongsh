# PONGSH - A Modern C Shell 💻

## Overview
PONGSH is a modern shell implemented in C with a focus on clean code architecture, visual appeal, and maintainability. Featuring custom implementations of essential shell commands, colorful interface with Unicode characters, and strict coding standards for professional development.

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

### 🏗️ Clean Architecture
- **Max 20 lines per function** - strict coding standards
- **Modular design** - organized in logical subdirectories
- **No #define in .c files** - all definitions in headers
- **5 functions max per file** - maintainable code structure

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
│   ├── my_string.c               # String manipulation (with my_strncmp)
│   └── my_utils.c                # General utilities
├── include/
│   ├── pongsh.h                  # Main project header
│   ├── colors.h                  # Color definitions & prototypes
│   ├── my_cat.h                  # Cat command header
│   ├── my_ls.h, my_cd.h, my_pwd.h, my_echo.h, my_printf.h
├── build/                        # Compiled objects & executables
├── Makefile                      # Advanced build system with subdirs
└── .gitignore
```

### 🔧 **Refactoring Highlights**
- **Function size limit**: All functions ≤ 20 lines
- **File organization**: Logical grouping by functionality
- **Subdirectory structure**: Clean separation of concerns
- **Build system**: Automatic detection of new subdirectories

## Building & Running
```sh
make
./build/bin/pongsh
```

## Usage

### 🚀 **Getting Started**
```sh
make              # Build the project
./build/bin/pongsh   # Launch PONGSH
```

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

### 🎨 **Modern Interface**
The shell features a beautiful, colorful interface:

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

## Recent Improvements 🎯

### v2.0 - Modern Architecture & Cat Command
- ✅ **Added `cat` command** with full file reading support
- ✅ **Refactored all functions** to ≤ 20 lines (strict limit)
- ✅ **Reorganized codebase** into logical subdirectories
- ✅ **Modern UI** with colors, emojis, and Unicode characters
- ✅ **Enhanced Makefile** with automatic subdirectory detection
- ✅ **Clean prompt** design: `user@hostname ~/path`

### Code Quality Standards 📏
- **Function Limit**: Maximum 20 lines per function
- **File Limit**: Maximum 5 functions per file  
- **Style Rules**: 
  - Variables declared at beginning only
  - No comments inside functions
  - No `#define` in .c files
  - Proper spacing between emojis and text
- **Architecture**: Modular design with logical separation

### Function Refactoring Examples 📝
**Before (31 lines):**
```c
void display_prompt(void) {
    // 31 lines of mixed logic
}
```

**After (10 lines):**
```c
void display_prompt(void) {
    char *current_path = get_current_path();
    if (!current_path) {
        display_fallback_prompt();
        return;
    }
    display_full_prompt(current_path);
    my_free(current_path);
}
```

---
