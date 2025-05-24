#!/usr/bin/env python3
from pwn import *

def check_memory_permissions():
    """Verify memory permissions before and after mprotect"""
    p = process('./vuln')
    gdb.attach(p, '''
        break *vulnerable
        break *0x080491b4  # int 0x80
        commands 1
            echo "Before mprotect:\\n"
            vmmap
            continue
        end
        commands 2
            echo "After mprotect:\\n"
            vmmap
            continue
        end
    ''')
    
    # Send exploit
    payload = cyclic(112)
    # [Add ROP chain here]
    
    p.sendline(payload)
    p.interactive()

if __name__ == "__main__":
    check_memory_permissions()
