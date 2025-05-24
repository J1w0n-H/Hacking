#include <stdio.h>
#include <stdlib.h>

void print_heap_and_stack_addresses() {
    // Heap allocation
    int *heap_buffer = malloc(20 * sizeof(int)); // Allocate for 20 integers
    if (heap_buffer == NULL) {
        perror("Failed to allocate heap memory");
        return;
    }

    printf("Heap addresses (increasing):\n");
    for (int i = 0; i < 20; i++) {
        printf("heap_buffer[%d] address: %p\n", i, (void*)&heap_buffer[i]);
    }

    // Stack allocation
    char stack_buffer[20]; // Allocate space on the stack for 20 chars

    printf("\nStack addresses (decreasing):\n");
    for (int i = 19; i >= 0; i--) { // Iterate from end to start
        printf("stack_buffer[%d] address: %p\n", i, (void*)&stack_buffer[i]);
    }

    free(heap_buffer); // Free the heap memory
}

int main() {
    print_heap_and_stack_addresses();
    return 0;
}

