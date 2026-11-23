# Objects, pointers and memory

## Storage and lifetime

- Distinguish scope, linkage and storage duration. Automatic objects usually
  live on the stack and allocated objects usually live on the heap. C defines
  their lifetimes independently of those implementation details. Static
  objects live for the program and thread-local objects for their thread.
- Initialize automatic and allocated objects before reading them. Returning
  an automatic object's address or retaining a pointer to it in longer-lived
  state leaves a dangling pointer. Check member, slice and callback-context
  lifetimes along with the original object.
- Document whether an API borrows, takes ownership of, or returns ownership of
  data. A borrowed pointer must stop being used before its owner frees,
  replaces, or successfully reallocates the object.

## Pointers and layout

- Use `&object` to take an address and `*ptr` to access the pointed-to object.
  In C, arguments are passed by value. To update a caller's pointer, return
  its replacement or accept a pointer to that pointer with a clear contract.
- Decide whether a null pointer is valid for each argument. A non-null value
  alone says nothing about bounds, alignment, lifetime or access rights.
- Use `const T *` for read-only access through a pointer and `T *const` for a
  fixed pointer binding. Convert object pointers through `void *` when the
  API requires generic data. Convert back to a suitable object pointer before
  dereferencing. Standard C provides neither arithmetic on `void *` nor
  a portable function-pointer round trip through `void *`.
- Keep pointer arithmetic within the same array object or its one-past
  position. The latter can delimit iteration but cannot be dereferenced.
  Subtract only pointers into the same array, including one-past, when the
  result fits `ptrdiff_t`. Avoid relational comparisons across allocations.
  Check the index before forming the pointer.
- Array parameters adjust to pointers. Pass lengths explicitly and use
  `sizeof array / sizeof array[0]` only where `array` still has array type.
  Match multidimensional array strides to the declared element type.
- Respect alignment and effective type. Use character types to inspect
  object representations and `memcpy` to copy bytes between suitably typed
  objects. Check that the resulting representation is valid before reading
  it as a value. Serialize fields explicitly when layout, padding or byte
  order can vary.

## Allocation and cleanup

- Use `malloc` for uninitialized storage and `calloc` when zeroed bytes fit
  the representation you need. All-bits-zero is not a portable null-pointer
  or floating-point initializer. Use typed initializers when required.
- Check additions and multiplications before allocation. For an element
  count, establish `count <= SIZE_MAX / sizeof *items` before multiplying.
  Check request limits and allocation results independently. Handle zero
  capacity explicitly rather than relying on zero-size allocation behavior.
- Grow with `realloc` using a temporary pointer and a nonzero request. On
  failure keep the original owner and capacity. On success replace the
  owner, commit the capacity, invalidate aliases and initialize new elements
  before reading them. Even when the address appears unchanged, old pointers
  to the previous allocation cannot be reused.
- Release only the allocation base pointer with the matching deallocator.
  `free(NULL)` is valid. Free each owned allocation once, including on
  partial failure, and account for ownership transferred to other objects.
  Clearing one pointer after `free` does not clear aliases.

For the underlying language rules, consult C11 draft sections 6.2.4, 6.3.2.3,
6.5, 6.5.6 and 7.22.3. [WG14 N1570](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf)
