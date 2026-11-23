# Strings, conversions and arithmetic

## Buffers and strings

- Specify capacity, used length and units at API boundaries. A C string
  requires a reachable terminating NUL. A byte span may contain embedded
  NULs and needs an explicit length. Validate termination within the known
  readable span before using a string function on arbitrary input.
- For a destination of capacity `cap`, a string of `len` bytes fits if
  `len < cap`. Define whether insufficient capacity means truncation,
  rejection, or reporting the required size. Check zero capacity before a
  write and ensure termination on every path that promises a string.
- Use writable storage for mutation. A string literal must not be modified.
  Document overlap restrictions, use `memmove` for overlapping valid ranges,
  and use `memcpy` for nonoverlapping ranges. Copy sizes are in bytes.
- `strncpy` pads short sources and may leave truncated output unterminated.
  For `snprintf`, check a negative result first, then compare the reported
  length with capacity to detect truncation. For `<ctype.h>`, pass EOF or a
  value representable as `unsigned char`.

## Conversions and arithmetic

- Pick types by domain. Prefer `size_t` for object sizes and counts and
  `ptrdiff_t` for representable pointer differences. Use fixed-width types
  when the interface requires an exact width and the implementation provides
  them. Match variadic format specifiers to the actual argument types.
- Check sign and range before narrowing or converting a potentially negative
  count to unsigned. Inspect integer promotions and usual arithmetic
  conversions in mixed-sign and narrow-type expressions. Casting a computed
  result to a wider type does not prevent overflow in the original operation.
- For text-to-integer conversion with `strtol`, reset `errno`, reject no
  digits and `ERANGE`, enforce the suffix policy through the end pointer,
  and range-check against the destination type. Enforce the desired sign,
  whitespace and base rules explicitly. For floating-to-integer conversion,
  reject non-finite and out-of-range values before casting.
- Signed overflow is undefined. Unsigned wrap is defined but can still
  invalidate a size or index. For `size_t` addition, check
  `a <= SIZE_MAX - b` before adding. For signed operations, use proven
  range checks or a checked-operation facility supported by the project.
- Check zero divisors and signed minimum divided or reduced modulo by
  `-1` when the quotient cannot be represented. Check shift counts against
  the promoted left operand's width and use an appropriate unsigned type
  for bit masks. Avoid negating the minimum signed value in its own type.

## Recursion

- Define a base case and a measure that decreases on each call. Handle invalid
  inputs before recursing and prove the largest supported depth.
- Use iteration or explicitly bounded work storage for unbounded input.
  Account for cycles in graph traversals and preserve the same result and
  failure semantics when changing traversal form. C does not guarantee
  tail-call optimization.
