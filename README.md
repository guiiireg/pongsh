# pongsh

Run `make test` to run all unit and integration suites.

## my_printf

`my_printf` writes to standard output through `write`. It returns the
number of bytes written, or `-1` on a write error, invalid format or
unsupported conversion. Text written before an error can remain visible.

Supported conversions are `%c`, `%s`, `%d`, `%i`, `%u`, `%o`, `%x`,
`%X`, `%p` and `%%`. Integer conversions support `hh`, `h`, `l`, `ll`
and `j`. The applicable flags, field width and precision are supported,
including widths and precisions supplied with `*`. Floating-point and
wide-character conversions are outside the current implementation.

## my_ls

Run `make my_ls`, then use `./my_ls [options] [path ...]`. With no path,
the program lists the current directory. Short listings use one entry per
line and bytewise name ordering. The supported options are `-a` (hidden
entries), `-l` (details), `-R` (recursive), `-d` (directory operands),
`-r` (reverse) and `-t` (most recent modification first). Options can
be grouped. Use `--` before operands that begin with a dash.

Run `make test-ls-unit` for the Unity suite and `make test-ls` to run the
unit and CLI integration tests.

## pongsh

Run `make` and start the shell with `./pongsh`. It reads commands from
standard input and shows a prompt on a terminal. It resolves external
commands through `PATH` or an explicit path and provides `cd`, `env`,
`setenv`, `unsetenv` and `exit` as builtins. Single and double quotes,
backslash escapes and semicolon-separated commands are supported. Pipes,
redirections, expansions and job control are outside this implementation.

Run `make test-pongsh` to exercise command execution, parsing, environment
changes, working-directory changes and exit statuses.
