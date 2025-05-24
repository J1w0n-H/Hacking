
// file2.c - This will be compiled into a shared library
#include <stdio.h>

// Shared variable and function definitions
int shared_value = 42;

void shared_function(void) {
    printf("Inside shared function\n");
}
