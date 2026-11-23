# Interfaces, undefined behavior and verification

## Implementation checks

- Put shared declarations in guarded headers and keep private functions and
  objects local to the translation unit. Keep declarations consistent with
  definitions and include the API header from its implementation. Respect
  the project's hosted, freestanding or platform-specific constraints.
- Check resource APIs using their documented return conventions. Treat short
  reads and writes according to the interface. Preserve the relevant error
  before cleanup if cleanup can change it. Check output state on partial
  failure and retries.
- Use callbacks with compatible function pointer types and a context that
  outlives their use. Avoid macros that evaluate an argument more than once.
  Use atomics or synchronization for shared mutable state when concurrent
  access is possible. `volatile` alone does not synchronize threads.

## Undefined behavior review

- Trace every dereference and library call back to valid initialization,
  bounds, alignment, effective type and lifetime. Include dangling pointers,
  buffer overflow, overlapping copies, uninitialized reads, and double free.
- Check signed overflow, invalid shifts, unsequenced accesses to the same
  scalar, and mismatched variadic arguments or callback signatures.
  Separate undefined behavior from implementation-defined choices such as
  plain `char` signedness and unspecified choices such as argument
  evaluation order. Avoid relying on choices the program does not control.
- Explain the invalid operation, its required preconditions and the input or
  state that violates them. Fix the underlying contract or operation rather
  than hiding the symptoms with a cast or compiler flag.

## Verification workflow

1. Build in the project's normal dialect with its existing warnings enabled.
   Add focused diagnostics such as conversion and format warnings for a
   local investigation when useful.
2. Run the available tests. Select relevant cases such as zero and one
   element, exact capacity and one byte short, minimum and maximum values,
   invalid input, allocation failure, overlap and partial initialization.
   Assert both the result and the post-failure state where applicable.
3. Where supported, compile and link a separate test build with
   `-g -fno-omit-frame-pointer -fsanitize=address,undefined`. Exercise the
   changed paths with that build. For leaks, use LeakSanitizer or a memory
   checker where supported. Sanitizer coverage is limited to executed paths.
4. For a failing case, preserve the smallest valid reproduction, inspect
   the first invalid operation with a debugger or sanitizer, and rerun both
   the focused case and the normal suite after fixing it.

Topic selection follows the [roadmap.sh C roadmap](https://roadmap.sh/c).
For C11 semantics, consult [WG14 N1570](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf)
and use the corresponding standard revision for the project's dialect.
