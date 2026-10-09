# Practical 10 - Investigating Inodes, Hard Links, Symbolic Links & mmap()

## Aim
To investigate Linux inode structures using `ls -i`, `stat`, and `find`,
to create and compare hard links and symbolic links, and to perform
file I/O using memory-mapped I/O (`mmap()`) vs traditional `read()`/`write()`.

## Objectives
- Examine inode numbers and file metadata using Linux commands.
- Create and compare hard links and symbolic links.
- Understand how links affect inode allocation, link counts, and file storage.
- Analyze behavior when original files are deleted.
- Use `mmap()` for memory-mapped file I/O.
- Compare `mmap()` with traditional `read()`/`write()`.

## Files
| File | Description |
|------|-------------|
| `inode_demo.sh` | Complete inode/hard link/symlink investigation script |
| `mmap_file.c` | File I/O using memory-mapped mmap() |
| `read_write_file.c` | Traditional file I/O using read()/write() |

## Run

### Inode and Link Investigation
```bash
bash inode_demo.sh
```

### mmap() vs read()/write() Comparison
```bash
# Compile
gcc -Wall -Wextra -g mmap_file.c      -o mmap_file
gcc -Wall -Wextra -g read_write_file.c -o read_write_file

# Create test file
echo "Linux memory mapped file I/O demonstration" > data.txt

# Test mmap version
./mmap_file
cat data.txt

# Reset file and test read/write version
echo "Linux memory mapped file I/O demonstration" > data.txt
./read_write_file
cat data.txt

# Performance test (large file)
dd if=/dev/zero of=test.dat bs=1M count=100
gcc -O2 mmap_file.c -o mmap_file
gcc -O2 read_write_file.c -o read_write_file
time ./mmap_file
time ./read_write_file
```

## Inode Concepts
```
Directory Entry → inode → Data Blocks
 (filename)       (metadata)  (content)
```

An **inode** stores:
- File type and permissions
- Owner (UID/GID)
- File size
- Timestamps (access, modify, change)
- Link count
- Pointers to data blocks

> **Note**: The filename is stored in the directory, NOT in the inode.

## Hard Links vs Symbolic Links

| Property | Hard Link | Symbolic Link |
|----------|-----------|---------------|
| Inode | Same as original | Own inode |
| Cross-filesystem | No | Yes |
| Directory links | No (usually) | Yes |
| If original deleted | File survives | Becomes dangling |
| `ls -l` indicator | No special indicator | Shows `-> target` |

## mmap() vs read()/write() Comparison

| Aspect | mmap() | read()/write() |
|--------|--------|---------------|
| Access method | Direct memory access | Explicit copy to buffer |
| System calls | Fewer (after mapping) | Per read/write call |
| Large file efficiency | Generally better | Multiple calls needed |
| Complexity | More complex | Simpler |
| Use case | Random access, large files | Sequential streaming |

## How mmap() Works
```
Disk File → mmap() → Virtual Address Space → Program accesses as array

data[0] = 'H';   // Directly modifies the mapped file page
msync();          // Flush changes to disk
munmap();         // Remove mapping
```
