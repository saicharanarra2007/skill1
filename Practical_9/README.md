# Practical 9 - File I/O: Low-Level vs Standard Library & dup2() Redirection

## Aim
To implement and compare file I/O using Linux low-level system calls
(`open`, `read`, `write`, `lseek`) versus standard C library streams
(`fopen`, `fread`, `fwrite`, `fseek`), and to demonstrate I/O redirection
using `dup2()`.

## Objectives
- Use low-level file I/O system calls with file descriptors.
- Implement the same operation using standard C library streams.
- Use `lseek()` / `fseek()` to examine and manipulate the file offset.
- Compare execution time of both approaches.
- Redirect `stdin` and `stdout` using `dup2()`.

## Files
| File | Description |
|------|-------------|
| `copy_lowlevel.c` | File copy using open/read/write/lseek |
| `copy_stdio.c` | File copy using fopen/fread/fwrite/fseek |
| `redirect_output.c` | Redirect stdout to a file using dup2() |
| `redirect_input.c` | Redirect stdin from a file using dup2() |

## Compile & Run

### File Copy Programs
```bash
gcc -Wall -Wextra -O2 copy_lowlevel.c -o copy_lowlevel
gcc -Wall -Wextra -O2 copy_stdio.c    -o copy_stdio

# Create test data
dd if=/dev/urandom of=input.dat bs=1M count=10

# Run both versions
./copy_lowlevel input.dat output_low.dat
./copy_stdio    input.dat output_stdio.dat

# Verify files are identical
cmp input.dat output_low.dat && echo "Low-level copy OK"
cmp input.dat output_stdio.dat && echo "Stdio copy OK"

# Checksums
sha256sum input.dat output_low.dat output_stdio.dat

# Performance comparison
time ./copy_lowlevel input.dat output_low.dat
time ./copy_stdio    input.dat output_stdio.dat
```

### I/O Redirection with dup2()
```bash
gcc -Wall -Wextra -g redirect_output.c -o redirect_output
gcc -Wall -Wextra -g redirect_input.c  -o redirect_input

# Output redirection
./redirect_output
cat output.txt

# Input redirection
printf "Operating Systems\nLinux File I/O\ndup2 system call\n" > input.txt
./redirect_input
```

## Standard File Descriptors
| FD | Name | Description |
|----|------|-------------|
| 0 | stdin | Standard Input (keyboard) |
| 1 | stdout | Standard Output (terminal) |
| 2 | stderr | Standard Error (terminal) |

## How dup2() Works
```
Before dup2(fd, STDOUT_FILENO):
  fd 1 (stdout) → Terminal
  fd 3 (fd)     → output.txt

After dup2(fd, STDOUT_FILENO):
  fd 1 (stdout) → output.txt   ← printf now writes here
  fd 3 (fd)     → output.txt   ← can be closed
```

## I/O Comparison
| Feature | Low-Level | Standard Library |
|---------|-----------|-----------------|
| Functions | open/read/write | fopen/fread/fwrite |
| Handle | File descriptor (int) | FILE pointer |
| Buffering | None (kernel buffers only) | User-space buffering |
| Portability | Linux/POSIX | C standard (all platforms) |
| lseek | `lseek()` | `fseek()` / `ftell()` |
