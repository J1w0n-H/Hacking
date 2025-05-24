#include <stdio.h>

int main() {
// Assign random value for each type or variables
	int i = 10;
	float f = 20.5;
	char c = 'A';
   	double d = 89.504489;

// Print value of variables each
	printf("Value of int : %d\n", i);
	printf("Value of float : %f\n", f);
	printf("Value of double : %f\n", d);
	printf("Value of char : %c\n", c);
	
	printf("\n"); 
// Print address of variables each
	printf("Address of int : %p\n", (void*)&i);
	printf("Address of float : %p\n", (void*)&f);
	printf("Address of char : %p\n", (void*)&c);
	printf("Address of double : %p\n", (void*)&d);

	printf("\n"); 
// Print size of variables each
	printf("Size of int : %d Byte\n", sizeof(i));
	printf("Size of float : %d Byte\n", sizeof(f));
	printf("Size of char : %d Byte\n", sizeof(c));
	printf("Size of double : %d Byte\n", sizeof(d));
	
	return 0;}
