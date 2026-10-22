---
name: c-rules
description: >-
  Mandatory coding standard for writing or modifying C code. Apply these
  rules to every C file, without exception.
---

# c-rules

Coding standard for C. Every rule below applies to any C code written or
modified. When refactoring existing code that breaks a rule, fix the code to
comply.

## Summary

| #  | Rule                                            |
|----|-------------------------------------------------|
| 1  | Relative include paths: `../../include/<file>.h` |
| 2  | Max 20 lines per function                       |
| 3  | Max 2 levels of nested control structures        |
| 4  | Max 4 parameters per function                    |
| 5  | Struct naming: `_s` tag, `_t` typedef            |
| 6  | Max 2 levels of pointer indirection              |
| 7  | Asterisk attached to the variable, not the type  |
| 8  | No comments inside functions; short doc comments outside |
| 9  | Variables declared at the top of the function; loop vars inside `for` |

## 1. Include paths

Always include project headers with a relative path, never with the bare
header name.

```c
// Correct
#include "../../include/my_header.h"

// Wrong
#include "my_header.h"
#include <my_header.h>
```

## 2. Function length

A function body must not exceed 20 lines. If it does, split the logic into
several smaller functions, each doing one thing.

## 3. Nested control structures

`if`, `else`, `switch`/`case`, `while` and `for` all count as nesting levels.
A function must not nest more than 2 of them. An `else if` chain does not add
a nesting level, but anything inside a branch of the chain does.

```c
// OK: 2 levels max
if (cond) {
    for (...) {
        ...
    }
}

// OK: else if chain does not add depth
if (a) {
    ...
} else if (b) {
    ...
}

// Wrong: 3 levels
if (a) {
    if (b) {
        while (...) {
            ...
        }
    }
}
```

If a function needs deeper nesting, extract the inner logic into a helper
function.

## 4. Function parameters

A function takes at most 4 parameters. If more values are needed, group them
in a struct and pass a pointer to it.

## 5. Struct naming

The struct tag ends with `_s`, the typedef ends with `_t`:

```c
typedef struct test_s {
    int value;
} test_t;
```

Do not name the typedef and the tag identically.

## 6. Pointer indirection

A variable must not have more than 2 levels of indirection (double pointers
are allowed, triple pointers are not):

```c
// Correct
int *a;
char **b;

// Wrong
int ***c;
```

If you need more than double indirection, restructure with an intermediate
struct or a table type.

## 7. Pointer declaration style

The asterisk is attached to the variable name, not the type:

```c
// Correct
int *ptr;
int **pptr;

// Wrong
int* ptr;
int *ptr, val;  // also avoid: declare each variable on its own line
```

## 8. Comments

No comments inside function bodies. Function bodies must contain only code —
explain yourself through naming and structure, not comments.

Comments are allowed outside functions, typically as a short header comment
above the function (doxygen style). Keep them brief and easy to scan:
one line for the description, short lines for the tags, no essays.

```c
/**
 * @brief Sort an array of integers in ascending order.
 * @param array: array to sort.
 * @param size: number of elements.
 * @return 0 on success, -1 on error.
 */
int sort_int_array(int *array, int size)
{
    ... // code only, no comments here
}
```

## 9. Variable declarations

Declare all local variables at the top of the function body, before any
statement. The exception is loop variables: a `for` loop may declare its
counter directly in its initializer.

```c
// Correct
int sum_values(int *array, int size)
{
    int sum = 0;
    int index = 0;

    for (int i = 0; i < size; i++)
        sum += array[i];
    return sum;
}

// Wrong: declaration after a statement
int sum_values(int *array, int size)
{
    int sum = 0;

    sum += array[0];
    int index = 1;  // wrong: not at the top of the function

    for (int i = index; i < size; i++)
        sum += array[i];
    return sum;
}
```


