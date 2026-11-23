# Advanced Git workflows

## Compare history and integrate changes

- Confirm which branch and remote are in scope. Use
  `git log --graph --oneline --decorate --all` for topology and
  `git log BASE..HEAD` for commits reachable from HEAD but absent from BASE.
  Use `git diff BASE...HEAD` to review the topic branch from the merge base.
- Use `git fetch REMOTE` to update remote-tracking refs without integrating
  changes into the current branch. Inspect the divergence before selecting
  a fast-forward, merge, rebase or squash. Follow the project's history policy.
- A fast-forward moves the branch tip. A merge can preserve both branches'
  histories. Rebase reapplies commits and changes their IDs. Squash
  combines changes into one commit. Cherry-pick selects specific commits
  and creates commits on the destination branch.
- Resolve conflicts in context and validate the merged behavior. Inspect
  `git status`, stage resolved paths and use the matching `--continue`
  command. Use the corresponding `--abort` when backing out of an operation
  started for the current task.

## Investigate and recover

- Use a separate worktree to isolate builds, compare revisions or investigate
  regressions without disturbing the active checkout. Check the branch
  association before creating or removing a worktree.
- Use `git bisect` with known good and bad revisions and a reproducible
  check. Mark untestable revisions as skipped and finish with
  `git bisect reset`. For `git bisect run`, return 0 for good, 1 for bad
  and 125 for a skipped revision when wrapping a binary test.
- Inspect local historical ref positions with `git reflog`. Recover a
  useful commit by creating a branch at its verified hash. Reflogs are
  local and expire. For a stash, inspect it and apply it first, then
  drop it only after confirming the restored changes.
- Prefer `git revert` for undoing shared commits. Before any reset,
  distinguish the branch tip, staging index and working tree.
  `--soft` moves the tip, `--mixed` also resets the index, and `--hard`
  also overwrites tracked working-tree changes. Obtain explicit authorization
  before destructive reset or rewriting shared history.

## Publish and collaborate

- Check the branch, remote, base, permissions and publication scope.
  A commit request covers local commits. Pushing and opening a pull
  request require separate authorization or an applicable authorized policy.
- Prefer normal pushes. If rewriting a remote branch is explicitly
  authorized, verify the expected current remote tip and use
  `--force-with-lease` with an explicit expected ref value.
- Review the complete topic diff before publishing. For a pull request,
  summarize the change, verification and any known limits. Check CI and
  branch protection. Fix hook or check failures at their source.
- For submodules, verify the recorded commit is available from the
  submodule remote and intended for the parent repository. Follow existing
  `.gitattributes` and Git LFS policies when staging files. Ensure the
  intended LFS pointer and object are available before publication.

Sources for the topic selection and command semantics are the
[Git and GitHub roadmap](https://roadmap.sh/git-github) and the
[Git reference manual](https://git-scm.com/docs).
