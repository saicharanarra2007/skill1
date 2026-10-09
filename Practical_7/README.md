# Practical 7 - Process Memory Layout Investigation

## Aim
To investigate the virtual memory layout of a Linux process using
`/proc/<PID>/maps`, `pmap`, and related kernel interfaces.

## Objectives
- Understand the different segments of a process's virtual address space.
- Examine code, data, BSS, heap, and stack segments.
- Use `/proc/<PID>/maps` and `pmap` to view memory mappings.
- Observe the role of ASLR (Address Space Layout Randomization).

## Files
| File | Description |
|------|-------------|
| `memory_demo.c` | Demo program that prints addresses of all memory segments |

## Compile & Run

```bash
gcc -Wall -Wextra -g memory_demo.c -o memory_demo
./memory_demo &
```

In another terminal:
```bash
# View process memory mappings
cat /proc/<PID>/maps

# Detailed mapping info
cat /proc/<PID>/smaps

# Memory statistics
grep -E "VmSize|VmRSS|VmData|VmStk|VmExe|VmLib" /proc/<PID>/status

# Using pmap utility
pmap <PID>

# Examine sections in the binary
readelf -S memory_demo
size memory_demo
```

## Memory Segments Explained
| Segment | Description | Permissions |
|---------|-------------|-------------|
| Code/Text | Executable instructions | r-xp |
| Data | Initialized global/static variables | rw-p |
| BSS | Uninitialized global/static variables | rw-p |
| Heap | Dynamic memory (malloc/calloc) | rw-p |
| Stack | Local variables, function call frames | rw-p |
| Shared Libraries | libc.so, ld-linux.so | r-xp |

## Key Concepts
- **Virtual Address Space**: Each process sees its own isolated address space.
- **ASLR**: Address Space Layout Randomization randomizes segment locations for security.
- **MMU**: The CPU's Memory Management Unit translates virtual to physical addresses.
- **Page Tables**: OS-maintained structures that map virtual pages to physical frames.

## Sample Output
```
Process ID (PID): 2456
Address of code   : 0x55c8a2b13169
Address of global : 0x55c8a2b16020
Address of static : 0x55c8a2b16024
Address of BSS    : 0x55c8a2b16028
Address of heap   : 0x55c8a4c6f2a0
Address of stack  : 0x7ffd8e5c9abc
```
