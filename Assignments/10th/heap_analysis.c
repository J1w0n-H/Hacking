#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Different privilege levels
enum UserType {
    GUEST = 0,
    USER = 1,
    ADMIN = 2,
    ROOT = 3
};

struct user_credentials {
    char username[32];
    char password[32];
    enum UserType type;    // User privilege level
    void (*access_handler)(struct user_credentials*);  // Function pointer for access control
};

struct file_access {
    char filename[64];
    enum UserType required_level;
    char content[128];
};

// Global variables to track allocations
struct user_credentials* current_user = NULL;
struct file_access* secret_file = NULL;

void normal_access(struct user_credentials* user) {
    printf("Normal access granted to %s with level %d\n", user->username, user->type);
}

void root_access(struct user_credentials* user) {
    printf("ROOT ACCESS granted! Spawning shell...\n");
    system("/bin/sh");
}

void setup_secret_file() {
    secret_file = malloc(sizeof(struct file_access));
    strcpy(secret_file->filename, "secret.txt");
    secret_file->required_level = ROOT;
    strcpy(secret_file->content, "Top secret content");
}

int main() {
    char choice[16];
    char buffer[128];
    int running = 1;

    setup_secret_file();

    printf("Heap Chunk Sizes:\n");
    printf("user_credentials: %zu\n", sizeof(struct user_credentials));
    printf("file_access: %zu\n", sizeof(struct file_access));
    
    while(running) {
        printf("\nUAF Exploitation Menu:\n");
        printf("1. Create normal user (small chunk)\n");
        printf("2. Create admin user (medium chunk)\n");
        printf("3. Try access file\n");
        printf("4. Free current user\n");
        printf("5. Reallocate chunk with custom data\n");
        printf("6. Display current user\n");
        printf("0. Exit\n");
        printf("Choice: ");
        
        fgets(choice, sizeof(choice), stdin);
        
        switch(choice[0]) {
            case '1': {
                current_user = malloc(sizeof(struct user_credentials));
                printf("Username: ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = 0;
                strncpy(current_user->username, buffer, 31);
                
                printf("Password: ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = 0;
                strncpy(current_user->password, buffer, 31);
                
                current_user->type = USER;
                current_user->access_handler = normal_access;
                printf("User created at: %p\n", (void*)current_user);
                break;
            }
            case '2': {
                // Larger allocation with extra data
                size_t size = sizeof(struct user_credentials) + 128;
                current_user = malloc(size);
                current_user->type = ADMIN;
                current_user->access_handler = normal_access;
                printf("Admin created at: %p\n", (void*)current_user);
                break;
            }
            case '3': {
                if(current_user && current_user->access_handler) {
                    current_user->access_handler(current_user);
                }
                break;
            }
            case '4': {
                if(current_user) {
                    printf("Freeing user at %p\n", (void*)current_user);
                    free(current_user);
                    // Intentionally not setting to NULL
                }
                break;
            }
            case '5': {
                // Reallocate the same size as user_credentials
                struct file_access* new_file = malloc(sizeof(struct user_credentials));
                memset(new_file, 'A', sizeof(struct user_credentials));
                // Overwrite function pointer in the previously freed chunk
                *(void**)(((char*)new_file) + offsetof(struct user_credentials, access_handler)) = root_access;
                printf("New allocation at: %p\n", (void*)new_file);
                break;
            }
            case '6': {
                if(current_user) {
                    printf("Current user at %p:\n", (void*)current_user);
                    printf("Username: %s\n", current_user->username);
                    printf("Type: %d\n", current_user->type);
                    printf("Handler: %p\n", (void*)current_user->access_handler);
                }
                break;
            }
            case '0':
                running = 0;
                break;
        }
    }
    return 0;
}
