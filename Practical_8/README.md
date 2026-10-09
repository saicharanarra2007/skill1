# Practical 8 - Dynamic Memory Allocation & Memory Leak Detection

## Aim
To develop C programs using `malloc()`, `calloc()`, `realloc()`, and `free()`,
observe dynamic memory allocation behavior, detect memory leaks using Valgrind,
and understand Copy-on-Write (COW) memory semantics with `fork()`.

## Objectives
- Use `malloc()`, `calloc()`, `realloc()`, and `free()` correctly.
- Understand how dynamically allocated memory is managed in the heap.
- Detect memory leaks and invalid memory operations using Valgrind.
- Observe Copy-on-Write (COW) behavior after `fork()`.

## Files
| File | Description |
|------|-------------|
| `memory_alloc_demo.c` | Demonstrates all four dynamic memory functions |
| `memory_leak_demo.c` | Intentional leaks for Valgrind demonstration |
| `cow_demo.c` | Copy-on-Write behavior with fork() |

## Compile & Run

### Memory Allocation Demo
```bash
gcc -Wall -Wextra -g memory_alloc_demo.c -o memory_alloc_demo
./memory_alloc_demo
```

### Valgrind - Detect Memory Leaks
```bash
gcc -Wall -Wextra -g memory_leak_demo.c -o memory_leak_demo

# Run without Valgrind
./memory_leak_demo

# Run with Valgrind (shows leaks)
valgrind --leak-check=full --show-leak-kinds=all ./memory_leak_demo
```

### Copy-on-Write Demo
```bash
gcc -Wall -Wextra -g cow_demo.c -o cow_demo
./cow_demo
```

## Dynamic Memory Functions Summary
| Function | Initialization | Use Case |
|----------|---------------|----------|
| `malloc(n)` | Uninitialized | General allocation |
| `calloc(n, size)` | Zero-initialized | Arrays |
| `realloc(ptr, n)` | Preserved + uninit | Resize allocation |
| `free(ptr)` | N/A | Release memory |

## Memory Layout (Heap)
```
Low Address
+------------------------+
|  Program Code (Text)   |
+------------------------+
|  Initialized Data      |
+------------------------+
|  BSS (uninitialized)   |
+------------------------+
|  Heap ↓ (grows down)   |  ← malloc/calloc/realloc
|                        |
|  Stack ↑ (grows up)    |  ← local variables
+------------------------+
High Address
```

## Copy-on-Write Concept
```
After fork():
  Parent → Virtual Page A → Physical Page X
  Child  → Virtual Page A → Physical Page X  (shared, COW marked)

After child writes to page A:
  Parent → Virtual Page A → Physical Page X  (original, unchanged)
  Child  → Virtual Page A → Physical Page Y  (new copy after COW)
```

## Valgrind Output Example
```
==12345== LEAK SUMMARY:
==12345==    definitely lost: 180 bytes in 3 blocks
==12345==    indirectly lost: 0 bytes in 0 blocks
==12345==    still reachable: 0 bytes in 0 blocks
==12345==         suppressed: 0 bytes in 0 blocks
```
