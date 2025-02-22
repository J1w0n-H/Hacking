#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define an enum to track the type of the variable
typedef enum {
    INT_TYPE,
    FLOAT_TYPE,
    CHAR_TYPE,
    DOUBLE_TYPE
} VarType;

// Define a union to hold variables of different types
typedef union {
    int i;
    float f;
    char c;
    double d;
} VarValue;

// Define a struct to hold both the type and value of the variable
typedef struct {
    VarType type;
    VarValue value;
} Var;

// Function prototypes
Var generateRandomVar();
const char* getTypeString(VarType type);
void printVarDetails(Var var, void* address);
void printTableHeader();

int main() {
    srand(time(NULL)); // Seed the random number generator
    
    // Define the size of the array
    const int ARRAY_SIZE = 20;
    Var varArray[ARRAY_SIZE];

    // Generate random variables and store them in the array
    for (int i = 0; i < ARRAY_SIZE; i++) {
        varArray[i] = generateRandomVar();
    }

    // Print table header
    printTableHeader();

    // Print details (type, address, and size) of each variable in tabular format
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printVarDetails(varArray[i], &varArray[i]);
    }

    return 0;
}

// Function to generate a random variable of random type
Var generateRandomVar() {
    Var var;
    int randomType = rand() % 4; // Randomly choose a type from 0 to 3

    switch (randomType) {
        case INT_TYPE:
            var.type = INT_TYPE;
            var.value.i = rand() % 100; // Random int from 0 to 99
            break;
        case FLOAT_TYPE:
            var.type = FLOAT_TYPE;
            var.value.f = (float)rand() / RAND_MAX * 100.0f; // Random float from 0.0 to 100.0
            break;
        case CHAR_TYPE:
            var.type = CHAR_TYPE;
            var.value.c = 'A' + (rand() % 26); // Random char from 'A' to 'Z'
            break;
        case DOUBLE_TYPE:
            var.type = DOUBLE_TYPE;
            var.value.d = (double)rand() / RAND_MAX * 100.0; // Random double from 0.0 to 100.0
            break;
    }

    return var;
}


// Function to print the table header
void printTableHeader() {
    printf("%-10s %-20s %-20s %-10s\n", "Type", "Address", "Value", "Size (bytes)");
    printf("--------------------------------------------------------------------\n");
}

// Function to print the variable's details: type, address, value, and size in tabular format
void printVarDetails(Var var, void* address) {
    switch (var.type) {
        case INT_TYPE:
            printf("%-10s %-20p %-20d %-10u\n", "int", address, var.value.i, sizeof(var.value.i));
            break;
        case FLOAT_TYPE:
            printf("%-10s %-20p %-20f %-10u\n", "float", address, var.value.f, sizeof(var.value.f));
            break;
        case CHAR_TYPE:
            printf("%-10s %-20p %-20c %-10u\n", "char", address, var.value.c, sizeof(var.value.c));
            break;
        case DOUBLE_TYPE:
            printf("%-10s %-20p %-20lf %-10u\n", "double", address, var.value.d, sizeof(var.value.d));
            break;
        default:
            printf("Unknown type\n");
            break;
    }
}

