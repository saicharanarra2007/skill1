#!/bin/bash
# Practical 10 - Investigating Inodes, Hard Links, and Symbolic Links
#
# Aim: To investigate Linux inode structures using ls -i, stat, and find,
# and to create hard and symbolic links.
#
# Run: bash inode_demo.sh

set -e

echo "================================================================"
echo "Practical 10 - Inodes, Hard Links, and Symbolic Links in Linux"
echo "================================================================"
echo ""

# Create working directory
WORKDIR="inode_lab_$$"
mkdir -p "$WORKDIR"
cd "$WORKDIR"

echo "Working directory: $(pwd)"
echo ""

# ----------------------------------------------------------------
# Step 1: Create a test file
# ----------------------------------------------------------------
echo "--- Step 1: Create a test file ---"
echo "Linux inode investigation" > original.txt
echo "Created: original.txt"
echo ""

# ----------------------------------------------------------------
# Step 2: View inode number using ls -i
# ----------------------------------------------------------------
echo "--- Step 2: ls -i (inode number) ---"
ls -li original.txt
echo ""

# ----------------------------------------------------------------
# Step 3: Investigate using stat
# ----------------------------------------------------------------
echo "--- Step 3: stat original.txt ---"
stat original.txt
echo ""

# ----------------------------------------------------------------
# Step 4: Create a Hard Link
# ----------------------------------------------------------------
echo "--- Step 4: Create a Hard Link ---"
ln original.txt hardlink.txt
echo "Created hard link: hardlink.txt -> same inode as original.txt"
echo ""
ls -li
echo ""

echo "--- Step 4b: stat comparison ---"
echo "=== original.txt ===" && stat original.txt | grep -E "Inode|Links"
echo "=== hardlink.txt ===" && stat hardlink.txt | grep -E "Inode|Links"
echo ""

# ----------------------------------------------------------------
# Step 5: Verify both names access the same data
# ----------------------------------------------------------------
echo "--- Step 5: Both names read same data ---"
echo "cat original.txt:  $(cat original.txt)"
echo "cat hardlink.txt:  $(cat hardlink.txt)"
echo ""

echo "--- Step 5b: Modify through hard link ---"
echo "Modified through hard link" >> hardlink.txt
echo "cat original.txt (after modifying via hardlink):"
cat original.txt
echo ""

# ----------------------------------------------------------------
# Step 6: Delete original, hard link still works
# ----------------------------------------------------------------
echo "--- Step 6: Delete original.txt ---"
rm original.txt
echo "original.txt removed."
ls -li
echo ""
echo "Data still accessible via hardlink.txt:"
cat hardlink.txt
echo ""

# ----------------------------------------------------------------
# Step 7: Create a Symbolic Link
# ----------------------------------------------------------------
echo "--- Step 7: Create a Symbolic Link ---"
echo "New file for symlink demo" > target.txt
ln -s target.txt symlink.txt
echo "Created symbolic link: symlink.txt -> target.txt"
echo ""

ls -li target.txt symlink.txt
echo ""
echo "Inode numbers are DIFFERENT (symlink has its own inode)."
echo ""

echo "--- Step 7b: stat symlink vs target ---"
echo "=== target.txt ===" && stat target.txt | grep -E "Inode|Links|File"
echo "=== symlink.txt ===" && stat symlink.txt | grep -E "Inode|Links|File"
echo ""

echo "cat symlink.txt: $(cat symlink.txt)"
echo ""

# ----------------------------------------------------------------
# Step 8: Delete the target - symlink becomes dangling
# ----------------------------------------------------------------
echo "--- Step 8: Delete target - Dangling symlink ---"
rm target.txt
echo "target.txt removed."
ls -li
echo ""
echo "Attempting to read symlink.txt (should fail - dangling):"
cat symlink.txt 2>&1 || true
echo ""
echo "ls -l shows dangling symlink:"
ls -l symlink.txt
echo ""

# ----------------------------------------------------------------
# Step 9: Find all hard links to an inode
# ----------------------------------------------------------------
echo "--- Step 9: Find all hard links using find ---"
# Create a fresh file for this demo
echo "Finding inodes" > findtest.txt
ln findtest.txt findtest_link.txt
INODE=$(ls -i findtest.txt | awk '{print $1}')
echo "Inode number of findtest.txt: $INODE"
echo "Finding all files with this inode:"
find . -inum "$INODE"
echo ""

# ----------------------------------------------------------------
# Step 10: Summary
# ----------------------------------------------------------------
echo "================================================================"
echo "Summary"
echo "================================================================"
echo "Hard Links:"
echo "  - Same inode number as original"
echo "  - File survives deletion of original name"
echo "  - Cannot span filesystems"
echo "  - Cannot link directories (usually)"
echo ""
echo "Symbolic Links:"
echo "  - Different inode (stores path to target)"
echo "  - Breaks if original is deleted (dangling symlink)"
echo "  - Can span filesystems"
echo "  - Can link directories"
echo ""

# Cleanup
cd ..
rm -rf "$WORKDIR"
echo "Cleanup done. Demo complete."
