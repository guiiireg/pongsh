# Repository Guidelines

## Project Structure

The repository contains `libmy`, a C11 static library. Public declarations live in `include/my.h`. General-purpose functions live in `lib/my/`, such as `lib/my/my_strlen.c`. The formatter sources live in `lib/my_printf/` and its private header lives in `include/my_printf_internal.h`. Keep all project C headers in `include/`. Keep helpers that are used in a single source file `static`. Limit each formatter source file to 100 lines and 10 function definitions.

The library Makefile builds both modules into `lib/my/libmy.a`. Keep the generated archive and object files out of version control.

## Build Commands

Run these commands from the repository root.

- `make -C lib/my` builds or updates the static library.
- `make -C lib/my re CFLAGS='-std=c11 -Wall -Wextra -Werror -pedantic'` rebuilds from scratch with strict compiler diagnostics.
- `make -C lib/my clean` removes intermediate object files and keeps the archive. `make -C lib/my fclean` also removes the archive.

## Coding Style

Use four spaces for C indentation and put function opening braces on their own line. Use `my_` for public function names and match each public declaration to its definition. Limit every function to four parameters and 20 lines. Use descriptive names and keep the C code free of comments.

Run `bash coding-style.sh . .` from the repository root to check Epitech style. Read `coding-style-reports.log` for file paths, line numbers, and rule IDs. Ignore C-G1 because this project does not require an Epitech banner. Fix the other reported violations and rerun the command. Use a clean source tree for the check, with generated build artifacts removed.

Production C code may call only `write`, `malloc`, `free`, and
project-defined functions such as `my_putchar`. Implement other operations
in the project. Standard types, constants and variadic macros are allowed.
This restriction applies to production code. Unity and its test harness may
use standard library and test-support functions.

## Testing

Run `make test` from the repository root to compile and run the Unity suite against a separate build of the static library. The test runner and its build artifacts live under `tests/`. Run `make clean` at the repository root to remove test build artifacts.

Add cases to `tests/test_libmy.c` using the `test_my_<function>` naming pattern and register them with `RUN_TEST`. Cover normal inputs and relevant boundaries, such as empty strings, integer limits, and partial output rows. When changing the public API, use `nm -g --defined-only lib/my/libmy.a` to verify the exported symbols.

## Commits and Pull Requests

Keep commits focused and use short, imperative subjects. Follow the existing scoped format, such as `feat(libmy): add library source files` or `build(libmy): deliver static library`. In a pull request, describe the behavior change, list the checks you ran, and link the relevant issue when one exists.
