#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to be called when the overflow is successful
void hacked_function() {
    printf("You've been hacked!\n");
}

// Vulnerable function that allows buffer overflow
void GetMachineName(char *Path, char MachineName[50]) {
    char *ServerName = MachineName;
    char *Temp = Path + 2;  // Skips the first two characters of the path

    // Vulnerable loop that copies too many characters into a small buffer
    while (*Temp != '\\' && *Temp != '\0') {
        *ServerName++ = *Temp++;
    }
    *ServerName = '\0';  // Null-terminate the string
}

// Function that indirectly calls the vulnerable function
void GetServerPath(char *Path, char **ServerPath) {
    char *FinalPath = Path;
    char MachineName[50];  // Vulnerable buffer size

    GetMachineName(Path, MachineName);  // Call the vulnerable function

    *ServerPath = FinalPath;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input>\n", argv[0]);
        return 1;
    }

    char *serverPath;
    GetServerPath(argv[1], &serverPath);  // Call the vulnerable function

    printf("Returned to main normally.\n");
    return 0;
}
