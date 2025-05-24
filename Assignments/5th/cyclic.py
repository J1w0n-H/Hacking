from pwn import *

# Find the offset using a 6-byte subsequence
offset = cyclic_find(b'aaaaba', n=6)
print(f"Offset: {offset}")
