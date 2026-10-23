# pongsh

![Language](https://img.shields.io/badge/language-C99-a8a8a8?logo=c)
![CI](https://github.com/guiiireg/pongsh/actions/workflows/unit_tests.yml/badge.svg)
![Coverage](https://img.shields.io/badge/tests-criterion%20%2B%20valgrind-blue)
![Progress](https://img.shields.io/badge/status-libc%20in%20progress-yellow)

A from-scratch reimplementation of the C standard library, with the final goal of building a complete shell. Only `write`, `malloc` and `free` are allowed — everything else is hand-written.

## Why this project

Understanding a system starts with rebuilding its foundations. By reimplementing the libc, I learn what actually happens behind `strlen`, `memcpy` or `strdup`: pointer arithmetic, memory ownership, undefined behavior at the edges. This library is the first milestone of a larger goal: a working shell, where these foundations become load-bearing — parsing a command line, managing processes, piping, handling signals.

The constraint of using only `write`, `malloc` and `free` is deliberate: no `printf`, no `strcpy`, no shortcuts. Every higher-level feature has to be earned by writing the layer underneath it.

## Implemented functions

### Memory (`string.h`)

| Function | Description | Status |
|---|---|---|
| `my_memcpy` | Copy a memory block to a non-overlapping destination | ✅ |
| `my_memmove` | Copy a memory block with overlap-safe handling | ✅ |
| `my_memset` | Fill a memory block with a byte value | ✅ |
| `my_memcmp` | Compare two memory blocks | ✅ |

### Strings (`string.h`)

| Function | Description | Status |
|---|---|---|
| `my_strlen` | Length of a null-terminated string | ✅ |
| `my_strcpy` | Copy a string | ✅ |
| `my_strncpy` | Copy at most n characters | ✅ |
| `my_strcat` | Concatenate a string | ✅ |
| `my_strncat` | Concatenate at most n characters | ✅ |
| `my_strcmp` | Compare two strings | ✅ |
| `my_strncmp` | Compare at most n characters | ✅ |
| `my_strdup` | Duplicate a string into a fresh allocation | ✅ |
| `my_strndup` | Duplicate at most n characters | ✅ |
| `my_strstr` | Locate a substring | ✅ |
| `my_revstr` | Reverse a string in place | ✅ |
| `my_strcapitalize` | Capitalize the first letter of each word, lowercase the rest | ✅ |
| `my_strlowcase` | Lowercase a string in place | ✅ |
| `my_strupcase` | Uppercase a string in place | ✅ |

### Output (`unistd.h`)

| Function | Description | Status |
|---|---|---|
| `my_putchar` | Write a single character to stdout | ✅ |
| `my_putstr` | Write a null-terminated string to stdout | ✅ |
| `my_put_nbr` | Write a signed integer to stdout | ✅ |

### Misc

| Function | Description | Status |
|---|---|---|
| `my_swap` | Swap two integers through pointers | ✅ |

### Planned

| Function | Description | Status |
|---|---|---|
| `my_printf` | Variadic formatted output (no libc `printf` allowed) | 🚧 |
| `my_itoa` / `my_atoi` | Number to string and back | 🚧 |
| `my_realloc` | Resize an allocation using only `malloc` / `free` | 🚧 |

Every implemented function ships with Criterion unit tests covering normal and edge cases.

## Build & usage

Requires `gcc` (or any C99 compiler). Tests additionally require [Criterion](https://github.com/Snaipe/Criterion).

```bash
make              # build libmy.a
make tests_run    # clean rebuild, then compile the test binary
./tests_libmy     # run the Criterion test suite
make clean        # remove object files
make fclean       # clean + remove libmy.a and the test binary
make re           # full rebuild
```

Link against the library in your own code:

```c
#include <stdlib.h>
#include "my.h"

int main(void)
{
    char *name = my_strdup("pongsh");

    my_putstr("hello from ");
    my_putstr(name);
    my_putchar('\n');
    free(name);
    return 0;
}
```

```bash
gcc main.c -Iinclude -L. -lmy -o hello
```

## Technical constraints

- **Authorized libc calls: `write`, `malloc`, `free` — nothing else.** No `printf`, no `strcpy`, no `exit`. This forces a hand-rolled output layer (`my_putchar`, `my_putstr`, `my_put_nbr`) and will force a homemade `my_printf` later.
- Strict in-house coding standard, enforced across the codebase:
  - functions limited to 20 lines, at most 4 parameters
  - at most 2 levels of nested control structures
  - struct tags end with `_s`, typedefs with `_t`
  - no comments inside function bodies; short Doxygen-style headers outside
  - variables declared at the top of each function
- Compilation with `-Wall -Wextra -Werror -std=c99`.

## Architecture

### Module layout

```
lib/
├── my/          core libc — strings, memory, basic output
└── my_printf/   formatted output (in progress), layered on top of my/
```

Each module gets its own directory and its own archive (`libmy.a`, `libmyprintf.a`, ...) so the frozen, fully tested core never mixes with the layers built on top of it.

Current state — a static library, fully tested:

```
lib/my/*.c ──► libmy.a ◄── include/my.h
                  │
                  └──► tests/*.c (Criterion) ──► tests_libmy
```

Target state — the shell pipeline this library is building toward:

```
        libmy.a
           │
   ┌───────▼────────────────────────┐
   │ REPL                             │
   │ read line ──► lexer ──► parser   │
   └───────┬────────────────────────┘
           │ token list ──► AST
   ┌───────▼──────────┐
   │ executor          │
   │ builtins          │  cd, env, exit
   │ external commands │  fork + execve
   │ pipes & redirects │  |, >, <, >>
   └───────┬──────────┘
           │
   signals & job control — SIGINT, SIGQUIT, jobs, fg/bg
```

Key design decisions will be documented here as the shell takes shape: environment model (copy-on-entry vs. shared `environ`), token structure, and the process model for pipelines.

## CI

Every push and pull request runs the [unit_tests](.github/workflows/unit_tests.yml) workflow:

1. Build Criterion v2.4.2 from source (with caching)
2. `make tests_run` — compile the library and the test suite
3. Run the Criterion tests
4. Re-run the full suite under Valgrind with `--leak-check=full`; any definite leak or memory error fails the build

## Roadmap

- [x] String primitives (`my_strlen`, `my_strcpy`, `my_strcmp`, ...)
- [x] Memory primitives (`my_memcpy`, `my_memmove`, `my_memset`, `my_memcmp`)
- [x] Output layer (`my_putchar`, `my_putstr`, `my_put_nbr`)
- [x] Allocation wrappers (`my_strdup`, `my_strndup`)
- [x] Criterion unit tests, CI with Valgrind leak checks
- [ ] `my_printf` and number conversion helpers
- [ ] Command line reading and tokenization
- [ ] Parser (tokens → AST)
- [ ] Builtins (`cd`, `env`, `exit`, ...)
- [ ] External commands (`fork` + `execve`)
- [ ] Pipes and redirections (`|`, `>`, `<`, `>>`, `<<`)
- [ ] Signal handling (`SIGINT`, `SIGQUIT`)
- [ ] Job control (`jobs`, `fg`, `bg`)

## License

No license has been chosen yet — this project is currently all-rights-reserved until a license file is added.
