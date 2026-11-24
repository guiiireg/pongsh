---
name: c-implementation
description: Implement, debug, review, and refactor C code with correct object lifetimes, pointer use, allocation and cleanup, arrays and strings, conversions, arithmetic, recursion, and defined behavior. Use when changing or investigating C code, especially APIs and boundary conditions.
---

# C Implementation

Apply this skill to C functions, modules and libraries. Use the project's C
dialect, API contracts, build flags and available dependencies. Apply the
repository's Epitech style skill alongside this one when it applies.

1. Read the public declaration and callers. Identify valid inputs, units for
   sizes, ownership, buffer capacity, aliasing, and the result and output
   state on failure. Preserve established behavior and clarify ambiguous
   contracts before relying on them.
2. Trace each pointer to a live object and verify its bounds, access rights
   and lifetime. Check sizes and arithmetic before operations that could
   overflow, access memory, or allocate resources.
3. Keep ownership changes explicit. Initialize resources, commit changes
   after successful operations, and release acquired resources on each exit.
   Preserve a usable state when an operation fails unless the API specifies
   a different outcome.
4. Compile and run the project's tests. Exercise the relevant boundaries and
   failure paths. When supported, run the affected code with AddressSanitizer
   and UndefinedBehaviorSanitizer in a separate build. Report checks run and
   any unverified assumptions.

## Production C in pongsh

Only `write`, `malloc`, `free`, and project-defined functions such as
`my_putchar` may be called. Implement string, formatting and memory
operations locally within this budget. The generic references describe
other APIs for projects that allow them. Standard types, constants and
variadic macros are available. The Unity test harness is outside this
production restriction.

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

## References

- [Objects, pointers and memory](references/memory.md) for storage duration,
  pointer operations, layout, ownership and allocation.
- [Strings, conversions and arithmetic](references/values.md) for buffers,
  numeric parsing, promotions, overflow and recursion.
- [Interfaces, undefined behavior and verification](references/verification.md)
  for translation units, error handling, portability, and debugging.

Read only the references relevant to the change. When reviewing, report the
source location, violated invariant, triggering conditions and proposed fix.
Distinguish confirmed behavior from a case that still needs verification.
