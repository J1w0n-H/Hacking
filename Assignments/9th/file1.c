// file1.c
#include <stdio.h>

// External variable and function declarations
extern int shared_value;
extern void shared_function(void);

// Static variable - only visible in this file
static int private_value = 100;

// Static function - only visible in this file
static void private_function(void) {
    printf("Inside private function, value: %d\n", private_value);
}

int main() {
    printf("Private value: %d\n", private_value);
    printf("Shared value: %d\n", shared_value);
    private_function();
    shared_function();
    return 0;
}

