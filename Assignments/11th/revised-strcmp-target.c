#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // Check arguments
    if (argc != 2) {
        printf("Usage: %s <password>\n", argv[0]);
        return 1;
    }

    const char *passwd = "foobar";  // Hardcoded password
    
    if (strcmp(passwd, argv[1]) == 0) {
        printf("Green light!\n");
    } else {
        printf("Red light!\n");
    }
    
    return 0;
}
