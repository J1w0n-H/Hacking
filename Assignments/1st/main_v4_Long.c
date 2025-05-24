#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define an enum to track the type of the variable
typedef enum {
    INT_TYPE,
    FLOAT_TYPE,
    CHAR_TYPE,
    DOUBLE_TYPE,
    LONG_LONG_TYPE,
    LONG_DOUBLE_TYPE
} VarType;

// Define a union to hold variables of different types
typedef union {
    int i;
    float f;
    char c;
    double d;
    long long int ll;
    long double ld;
} VarValue;

// Define a struct to hold both the type and value of the variable
typedef struct {
    VarType type;
    VarValue value;
} Var;

// Function prototypes
Var generateRandomVar();
void printVarDetails(Var var, void* address);
void printTableHeader();
size_t getVarSize(Var var);

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
    int randomType = rand() % 6; // Randomly choose a type from 0 to 5

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
        case LONG_LONG_TYPE:
            var.type = LONG_LONG_TYPE;
            var.value.ll = (long long int)rand() * rand(); // Random long long int
            break;
        case LONG_DOUBLE_TYPE:
            var.type = LONG_DOUBLE_TYPE;
            var.value.ld = (long double)rand() / RAND_MAX * 100.0; // Random long double from 0.0 to 100.0
            break;
    }

    return var;
}


// Function to print the table header
void printTableHeader() {
    printf("%-15s %-20s %-30s %-10s\n", "Type", "Address", "Value", "Size (bytes)");
    printf("------------------------------------------------------------------------------\n");
}

// Function to print the variable's details: type, address, value, and size in tabular format
void printVarDetails(Var var, void* address) {
    size_t size = getVarSize(var);

    switch (var.type) {
        case INT_TYPE:
            printf("%-15s %-20p %-30d %-10zu\n", "int", address, var.value.i, size);
            break;
        case FLOAT_TYPE:
            printf("%-15s %-20p %-30f %-10zu\n", "float", address, var.value.f, size);
            break;
        case CHAR_TYPE:
            printf("%-15s %-20p %-30c %-10zu\n", "char", address, var.value.c, size);
            break;
        case DOUBLE_TYPE:
            printf("%-15s %-20p %-30lf %-10zu\n", "double", address, var.value.d, size);
            break;
        case LONG_LONG_TYPE:
            printf("%-15s %-20p %-30lld %-10zu\n", "long long", address, var.value.ll, size);
            break;
        case LONG_DOUBLE_TYPE:
            printf("%-15s %-20p %-30Lf %-10zu\n", "long double", address, var.value.ld, size);
            break;
        default:
            printf("Unknown type\n");
            break;
    }
}

// Function to get the size of the variable based on its type
size_t getVarSize(Var var) {
    switch (var.type) {
        case INT_TYPE:
            return sizeof(var.value.i);
        case FLOAT_TYPE:
            return sizeof(var.value.f);
        case CHAR_TYPE:
            return sizeof(var.value.c);
        case DOUBLE_TYPE:
            return sizeof(var.value.d);
        case LONG_LONG_TYPE:
            return sizeof(var.value.ll);
        case LONG_DOUBLE_TYPE:
            return sizeof(var.value.ld);
        default:
            return 0; // Unknown type
    }
}

