# Repository Guidelines

## Project Structure

The repository contains `libmy`, a C11 static library. Public declarations live in `include/my.h`. General-purpose functions live in `lib/my/`, such as `lib/my/my_strlen.c`. The formatter sources live in `lib/my_printf/` and its private header lives in `include/my_printf_internal.h`. Keep all project C headers in `include/`. Keep helpers that are used in a single source file `static`. Limit each formatter source file to 100 lines and 10 function definitions.

The library Makefile builds both modules into `lib/my/libmy.a`. Keep the generated archive and object files out of version control.

The `my_ls` executable starts in `lib/my_ls/my_ls.c`. Keep its directory
traversal, output and option parsing in the corresponding subdirectories
and its declarations in `include/my_ls.h`.

The `pongsh` executable starts in `src/main.c`. Its builtins, environment,
execution, input and parser modules live under `src/`. Shared declarations
live in `include/pongsh.h`.

## Build Commands

Run these commands from the repository root.

- `make` or `make pongsh` builds the interactive shell.
- `make my_ls` builds the `my_ls` executable.
- `make -C lib/my` builds or updates the static library.
- `make -C lib/my re CFLAGS='-std=c11 -Wall -Wextra -Werror -pedantic'` rebuilds from scratch with strict compiler diagnostics.
- `make -C lib/my clean` removes intermediate object files and keeps the archive. `make -C lib/my fclean` also removes the archive.

## Coding Style

Use four spaces for C indentation and put function opening braces on their own line. Use `my_` for public function names and match each public declaration to its definition. Limit every function to four parameters and 20 lines. Use descriptive names and keep the C code free of comments. Name project structure tags with `_s` and their typedef aliases with `_t`, as in `typedef struct shell_s { … } shell_t;`.

After every change to a project `.c` or `.h` file, run `make clean` and then `bash coding-style.sh . .` from the repository root to check Epitech style. Read `coding-style-reports.log` for file paths, line numbers, and rule IDs. Ignore C-G1 because this project does not require an Epitech banner. Fix the other reported violations and rerun the command. Use a clean source tree for the check, with generated build artifacts removed.

Production C code may call only `write`, `malloc`, `free`, and
project-defined functions such as `my_putchar`. Implement other operations
in the project. Standard types, constants and variadic macros are allowed.
This restriction applies to production code. Unity and its test harness may
use standard library and test-support functions.

The `my_ls` module also allows `opendir`, `readdir`, `closedir`,
`stat`, `lstat`, `getpwuid`, `getgrgid`, `time`, `ctime`,
`readlink`, `perror`, `strerror` and `exit`. Use `errno` as needed with
these APIs. Other modules retain their existing restrictions.

The shell in `src/` may call project functions and the following external
functions: `malloc`, `free`, `exit`, `opendir`, `readdir`, `closedir`,
`getcwd`, `chdir`, `fork`, `stat`, `lstat`, `fstat`, `open`, `close`,
`getline`, `strtok`, `strtok_r`, `read`, `write`, `execve`, `access`,
`isatty`, `wait`, `waitpid`, `wait3`, `wait4`, `signal`, `kill`,
`getpid`, `strerror`, `perror` and `strsignal`. Standard types, macros and
`errno` are available. This list applies only to the shell.

## Testing

Run `make test` from the repository root to run all unit and integration
tests for `libmy`, `my_ls`, and `pongsh`. Run `make test-libmy` for only
the library tests. Run `make clean` to remove test build artifacts.

Run `make test-pongsh` for the shell integration tests.

Run `make test-ls-unit` for the Unity cases in `tests/test_my_ls.c`. Run
`make test-ls` for those cases and the listing CLI tests against filesystem
fixtures.

Add cases to `tests/test_libmy.c` using the `test_my_<function>` naming pattern and register them with `RUN_TEST`. Cover normal inputs and relevant boundaries, such as empty strings, integer limits, and partial output rows. When changing the public API, use `nm -g --defined-only lib/my/libmy.a` to verify the exported symbols.

## Commits and Pull Requests

Keep commits focused and use short, imperative subjects. Follow the existing scoped format, such as `feat(libmy): add library source files` or `build(libmy): deliver static library`. In a pull request, describe the behavior change, list the checks you ran, and link the relevant issue when one exists.
