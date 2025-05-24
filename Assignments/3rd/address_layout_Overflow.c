#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int global_var_1 = 0;
int global_var_2 = 0;

int global_uninit_var_1;
int global_uninit_var_2;

void stack_overflow_function() {
    char stack_buffer[10]; // Small buffer for stack overflow

    // Intentionally write beyond the stack buffer
    for (int i = 0; i <= 10; i++) { // Writing 11 characters into a 10-byte buffer
        stack_buffer[i] = 'A'; // This will cause a stack overflow on the 11th iteration
        printf("stack_buffer[%d] address: %p\n", i, (void*)&stack_buffer[i]); // Print the address of each element
    }
}
int main() {
    int local_var_1 = 0;
    int local_var_2 = 0;
    int local_var_3 = 0;

    // Allocate memory on the heap
    int *ptr_1 = malloc(10 * sizeof(int)); // Small allocation
    int *ptr_2 = malloc(10 * sizeof(int)); // Another small allocation

    // Intentionally cause a heap overflow
    // Call a function that causes stack overflow
    stack_overflow_function();

    // Print addresses for debugging
    printf("Local var 1 address: %p\n", (void*)&local_var_1);
    printf("Local var 2 address: %p\n", (void*)&local_var_2);
    printf("Local var 3 address: %p\n", (void*)&local_var_3);
    printf("Heap var 1 address: %p\n", (void*)ptr_1);
    printf("Heap var 2 address: %p\n", (void*)ptr_2);
    printf("Global (uninit) var 1 address: %p\n", (void*)&global_uninit_var_1);
    printf("Global (uninit) var 2 address: %p\n", (void*)&global_uninit_var_2);
    printf("Global var 1 address: %p\n", (void*)&global_var_1);
    printf("Global var 2 address: %p\n", (void*)&global_var_2);
   
    free(ptr_1);
    free(ptr_2);

    return 0;
}

