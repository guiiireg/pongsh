---
name: epitech-c-coding-style
description: Enforce Epitech C coding style when generating, reviewing, fixing, or refactoring C code, excluding the mandatory Epitech header rule C-G1.
---

# Epitech C Coding Style

Use this skill for C generation, review, fixes and refactoring, from a single
file to an entire project. Read [the active rules and checker coverage](references/coding-style.md)
before working.

C-G1 is permanently disabled. Never add, generate, require or report a missing
Epitech banner. Apply C-H2 include guards independently.

Apply explicit user instructions first, project requirements second, active
style rules third, and general C practices last. Report conflicts with project
requirements and preserve the expected behavior.

In pongsh, also enforce the production API restriction in `AGENTS.md`.
The allowed calls are `write`, `malloc`, `free`, and project-defined
functions such as `my_putchar`. Unity and test tooling are outside this
restriction.

- **Generate.** Apply the active rules as you write. Keep functions focused,
  split translation units when they reach their limits and use only necessary
  dependencies. Compile with the project's normal build.
- **Review.** In pongsh, run `bash coding-style.sh . .` from the root and
  read `coding-style-reports.log`. Ignore C-G1 and fix every other reported
  violation in scope. Rerun the command after fixes. Check the report even
  when the exit status reflects ignored C-G1 findings. For projects without
  the official wrapper, use the bundled checker as described in the
  reference. Report confirmed findings with file, line, rule ID and a
  concrete fix. Label uncertain findings as requiring review.
- **Fix or refactor.** Preserve behavior and keep the diff scoped. Extract
  focused helpers, flatten deep control flow and reduce excessive parameters
  using coherent types when appropriate. Preserve useful comments outside
  functions. Compile and run the available project tests after editing.
