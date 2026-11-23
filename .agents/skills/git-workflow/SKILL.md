---
name: git-workflow
description: Inspect Git changes, verify what belongs in version control, plan atomic commits, and create them when authorized. Use for staging, commit review, branch integration, Git recovery, and GitHub delivery workflows.
---

# Git Workflow

## Inspect and plan

1. Read the repository instructions and recent commit messages. Identify the
   current branch and whether a merge, rebase or cherry-pick is in progress.
   Start with `git status --short --branch`, `git diff`,
   `git diff --cached` and `git log -6 --oneline`.
2. Inspect untracked files separately. Verify that each proposed path belongs
   to the task. Follow the repository's treatment of generated deliverables.
   Exclude incidental build output, local configuration and secrets. Check
   ignore rules with `git check-ignore -v -- PATH` when relevant.
3. Propose commits in dependency order. Each commit should express one
   coherent intent and be independently reviewable. Keep necessary tests,
   interfaces and implementation together when separating them would break
   the build or make the behavior difficult to verify. Prefer short,
   imperative subjects in the repository's format, such as
   `feat(libmy): add library source files`.

## Stage and commit

Treat a request to inspect or propose a split as read-only. Create commits
when the user explicitly requests them or when an applicable, authorized
automation policy grants that action. A request to commit the work already
authorizes routine staging for that scope. Respect required tool approvals.
Check publication and history rewriting separately.

Stage only the agreed paths or hunks with `git add -- PATH` or `git add -p`.
Identify pre-staged unrelated changes before touching the index. If mixed
staging prevents a clean commit, preserve it and resolve the scope before
committing. Review `git diff --cached --stat`, `git diff --cached --check`
and the full staged diff before each commit. Check that the staged snapshot
contains what was tested, especially after partial staging. Run applicable
checks and investigate hook failures.

After each commit, verify its subject and paths with
`git show --stat --oneline HEAD` and recheck status. Report the commit IDs
and any pending changes. Read [advanced Git workflows](references/advanced-git.md)
when integrating branches, investigating history, recovering changes or
publishing to GitHub.
