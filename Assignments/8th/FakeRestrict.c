#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char command[200];
    printf("Enter command to ban: ");
    fgets(command, sizeof(command), stdin);

    // Remove newline character from command if present
    command[strcspn(command, "\n")] = 0;
    
    // Build the alias command to add to .bashrc
    char command1[100] = "echo 'alias ";
    char command2[100] = "=\"echo restricted\"' >> ~/.bashrc";
    
    strcat(command, command2);
    strcat(command1, command);
    printf("Banning using: %s\n", command1);
    system(command1);

    // Inform the user to reload the .bashrc file or restart the shell
    printf("Alias added. Run 'source ~/.bashrc' or restart the terminal to activate.\n");
    
    return 0;
}

