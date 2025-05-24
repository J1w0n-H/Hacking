#include <stdio.h>

void printTableHeader();

int main() {
// Assign random value for each type or variables

    int i = 10;
    float f = 20.5;
    char c = 'A';
    double d = 89.504489;

// Print header for table
    printTableHeader();
	
// Print table values
    printf("%-15s %-20p %-30d %-10u\n", "int", (void*)&i, i, sizeof(i));
    printf("%-15s %-20p %-30f %-10u\n", "float", (void*)&f, f, sizeof(f));
    printf("%-15s %-20p %-30c %-10u\n", "char", (void*)&c, c, sizeof(c));
    printf("%-15s %-20p %-30f %-10u\n", "double", (void*)&d, d, sizeof(d));

    return 0;}


// A function to print the header of the table
void printTableHeader() {
    printf("%-15s %-20s %-30s %-10s\n", "Type", "Address", "Value", "Size (bytes)");
    printf("-------------------------------------------------------------------------\n");
}

