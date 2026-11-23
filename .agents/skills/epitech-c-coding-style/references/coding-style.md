# Epitech C coding style

Use these rules for first-party C code. Honor subject-specific restrictions.
In particular, `for`, `while`, `switch`, `break` and `continue` are available
unless the subject restricts them.

## File organization

- **C-O1** Keep unused and generated files such as object files, executables
  and temporary files out of the repository.
- **C-O2** Use `.c` for C source and `.h` for C headers.
- **C-O3** A `.c` file may define at most ten functions, with at most five
  non-`static` definitions. Prototypes do not count.
- **C-O4** Use explicit English snake_case names for files and directories.

## Global rules

- **C-G1** Permanently disabled. Ignore Epitech banners, including their absence.
- **C-G2** Separate functions by exactly one blank line.
- **C-G3** Indent preprocessor directives consistently with their nesting.
- **C-G4** Use immutable file-scope objects. Mutable globals are forbidden,
  including file-scope `static` variables.
- **C-G5** Include header files only.
- **C-G6** Use Unix line endings and avoid backslash line continuations.
- **C-G7** Remove trailing whitespace.
- **C-G8** Start with content and avoid extra blank lines at EOF.
- **C-G9** Give meaningful names to constants in place of magic numbers.
- **C-G10** Do not use inline assembly.

## Functions

- **C-F1** Give each function one responsibility.
- **C-F2** Use explicit English snake_case names for functions.
- **C-F3** Use at most 80 columns per line.
- **C-F4** Use at most 20 physical lines between a function's opening and
  closing braces, including blank lines.
- **C-F5** Use at most four parameters. Count a variadic ellipsis as a slot.
- **C-F6** Write `(void)` for an empty parameter list.
- **C-F7** Pass structures by pointer.
- **C-F8** Keep comments outside functions.

## Layout

- **C-L1** Write one instruction per line.
- **C-L2** Indent with four spaces per level and no tabs.
- **C-L3** Use conventional spaces around operators, after commas and after
  control keywords. Keep unary operators attached to their operands.
- **C-L4** Put a function's opening brace on its own line. Place the opening
  brace of a condition or loop on the same line as its controlling expression.
- **C-L5** Declare local variables at the start of the function. Use one
  declaration per instruction.
- **C-L6** Separate the declarations from the instructions with exactly one
  blank line. Avoid other blank lines in function bodies.

## Variables and types

- **C-V1** Use English snake_case identifiers, `_t` suffixes for typedefs and
  UPPER_SNAKE_CASE for macros, file-scope constants and enum values.
- **C-V2** Keep structures coherent and as small as possible.
- **C-V3** Attach the pointer asterisk to its identifier, as in `int *ptr`.

## Control flow

- **C-C1** Keep control flow below three nested levels, counting each
  `else if` as another level in the chain.
- **C-C2** Use simple ternaries only when consuming the result. Avoid nested
  or chained ternaries.
- **C-C3** Do not use `goto`.

## Headers

- **C-H1** Put prototypes, types, structures, enums, global declarations and
  macros in the appropriate headers.
- **C-H2** Enclose each header with matching `#ifndef`, `#define` and
  `#endif` directives.
- **C-H3** Keep macros simple and on a single physical line. Avoid hiding
  complex code in macros.

## Advanced rules

- **C-A1** Qualify pointed-to data as `const` when it must remain immutable.
- **C-A2** Select types that express the required range and purpose, such as
  `size_t` for sizes or `uint32_t` for a specified 32-bit value.
- **C-A3** End each file with a newline.
- **C-A4** Mark file-scope functions and objects `static` when they are used
  only in their translation unit.

## Checking style in pongsh

Run `bash coding-style.sh . .` from the repository root. Read the generated
`coding-style-reports.log` and ignore C-G1. Correct other findings and rerun
the same command. Bundled checker coverage below applies to projects that
lack the official wrapper or to supplemental diagnostics.

## Bundled checker coverage

Run with Python 3.10+ and Clang on PATH. The scanner checks physical text and
uses Clang's C AST for structural checks. It skips symlinked entries during
recursive discovery. Check only first-party directories when dependencies
have their own coding style.

- **Automatic** C-G6, C-G7, C-G8, C-F3, C-H2, C-A3.
- **Automatic for ordinary, directly written declarations and statements**
  C-O3, C-G2, C-G4, C-G5, C-G10, C-F2, C-F4, C-F5, C-F6, C-F8, C-L2,
  C-L4, C-L5, C-C1, C-C2, C-C3, C-H3. The checker limits C-G2 to adjacent
  definitions separated solely by whitespace, C-G5 to literal includes of
  source or object files, C-F2 to identifier shape, C-L2 to tabs and the basic
  indentation grid, C-C2 to nested or chained ternaries, and C-H3 to physical continuations. Review other aspects
  of these rules manually, including macro expansions and inactive branches.
- **Manual** C-O1, C-O2, C-O4, C-G3, C-G9, C-F1, C-F7, C-L1, C-L3,
  C-L6, C-V1, C-V2, C-V3, C-H1, C-A1, C-A2, C-A4. Validate
  repository scope, type semantics, layout and language choices in context.

`--json` returns an object with `diagnostics` and `analysis_errors` arrays.
Without `--strict`, Clang failures are reported separately and reliable
text checks still run. `--strict` requires successful analysis of every
file. Exit status 1 means confirmed style violations. Exit status 2 means
invalid input or incomplete strict analysis. Review unparsed files before
claiming complete coverage.

Use repeated arguments such as `--clang-arg=-Iinclude --clang-arg=-DFEATURE=1`
to select the project's build configuration. Repeat the check for other
supported configurations when they expose different branches.
