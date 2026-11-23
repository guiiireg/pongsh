# pongsh

## my_printf

`my_printf` writes to standard output through `write`. It returns the
number of bytes written, or `-1` on a write error, invalid format or
unsupported conversion. Text written before an error can remain visible.

Supported conversions are `%c`, `%s`, `%d`, `%i`, `%u`, `%o`, `%x`,
`%X`, `%p` and `%%`. Integer conversions support `hh`, `h`, `l`, `ll`
and `j`. The applicable flags, field width and precision are supported,
including widths and precisions supplied with `*`. Floating-point and
wide-character conversions are outside the current implementation.
