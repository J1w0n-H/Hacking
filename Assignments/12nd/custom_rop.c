// custom_rop.c
// Demonstrates custom ROP gadgets and privilege operations

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

// Custom gadget functions - these will be used in our ROP chain
void set_eax() {
    asm("pop %eax");  // Pop value into eax
    asm("ret");       // Return to continue ROP chain
}

void set_ebx() {
    asm("pop %ebx");  // Pop value into ebx
    asm("ret");       // Return to continue ROP chain
}

void do_syscall() {
    asm("int $0x80"); // Perform syscall
    asm("ret");       // Return to continue ROP chain
}

// Function to print current privileges
void print_privileges() {
    printf("Current UID: %d\n", getuid());
    printf("Current EUID: %d\n", geteuid());
}

void gadget1() {
    asm("xor %edx, %edx"); // Zero out edx
    asm("ret");            // Return to continue ROP chain
}

void gadget2() {
    asm("xor %ecx, %ecx"); // Zero out ecx
    asm("ret");            // Return to continue ROP chain
}

void vulnerable_func(char* input) {
    char buffer[64];
    // Intentionally vulnerable strcpy
    strcpy(buffer, input);
}

int main(int argc, char** argv) {
    if(argc < 2) {
        printf("Usage: %s <input>\n", argv[0]);
        return 1;
    }

    printf("Before exploitation:\n");
    print_privileges();
    
    printf("\nAttempting ROP chain...\n");
    vulnerable_func(argv[1]);
    
    printf("\nAfter exploitation:\n");
    print_privileges();
    
    return 0;
}
