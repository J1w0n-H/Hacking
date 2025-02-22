#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char filename[100];
    printf("Enter file name to compile: ");
    fgets(filename, sizeof(filename), stdin);

    // Remove newline character from filename if present
    filename[strcspn(filename, "\n")] = 0;

    // Build command to compile. For example, if the input
    // file name is a.c, command will hold "gcc -o a.out a.c"
    char command[150] = "gcc -o a.out ";
    strcat(command, filename);

    printf("Compiling file using: %s\n", command);
    system(command);

    // Make the output file executable with chmod +x
    system("chmod +x a.out");

    printf("\nRunning file:\n");
    system("./a.out");

    return 0;
}

