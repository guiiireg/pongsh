---
name: c-validation
description: Build, test, diagnose, and fix C code. Use to validate a C change or investigate a failing build, linker error, test, runtime defect, sanitizer report, or coding-style check.
---

# C Validation

## Establish a baseline

Read the project's contributor guide, build targets and test configuration.
Identify the affected entry points, C dialect, flags and dependencies. Use
the project's normal targets first. Save the command, exit status and first
actionable diagnostic. If a target combines building and testing, determine
whether the test executable actually ran.

## Diagnose and correct

| Category | Evidence | Next action |
| --- | --- | --- |
| Build | Preprocessor, compiler, linker or build-tool failure | Fix the first root cause, rebuild and check whether later diagnostics disappear. Separate environment or dependency failures from source defects. |
| Behavior | A failing assertion, incorrect output, crash, or sanitizer report | Reproduce the failure, compare the actual result with the API contract and fix the violated invariant. Add a focused regression test when needed. |
| Style | A confirmed rule violation from the checker or a manual review | Apply the project's style rules with a scoped edit and preserve observable behavior. Report checker limitations separately. |

Classify a warning promoted to an error according to its cause and note that
it blocks the build. Preserve existing tests and build flags unless the
change requires updating them. Use `c-implementation` for C correctness and
`epitech-c-coding-style` for Epitech rules when applicable. For a review-only
request, report findings and fixes without editing files.

## Verify the fix

Rerun the failing check first, then the regular build and test suite. Run
style checks on affected first-party files. When useful and supported,
use a separate build with AddressSanitizer and UndefinedBehaviorSanitizer.
Avoid reusing objects compiled with different flags. Report the commands,
results and any checks blocked by missing dependencies or unsupported tools.

## Commands for pongsh

- Run `make test` from the root to build and execute the Unity suite.
- For a fresh strict build, use a new temporary directory with
  `make test BUILD_DIR=/path/to/temp CFLAGS='-std=c11 -Wall -Wextra -Werror -pedantic'`.
- Build the production library with `make -C lib/my` when validating
  delivery of the generated `lib/my/libmy.a`.
- Verify that production code calls only `write`, `malloc`, `free`,
  and project-defined functions such as `my_putchar`. Inspect new call
  sites and, when useful, check optimized library objects with `nm -u`.
  Distinguish toolchain runtime symbols from source-level calls.
  Unity tests and tooling may use the standard library.
- Build `my_ls` with `make my_ls` and exercise the CLI with
  `make test-ls`. The extra functions listed for `my_ls` in
  `AGENTS.md` apply only to that module.
- Check Epitech style with `bash coding-style.sh . .` from the repository
  root. Keep generated build artifacts outside the scanned tree or clean
  them first. Read `coding-style-reports.log`, ignore C-G1, fix the other
  reported violations and rerun the command.
