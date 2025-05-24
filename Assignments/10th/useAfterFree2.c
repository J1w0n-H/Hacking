//gcc useAfterFree2.c -o useAfterFree2 -mpreferred-stack-boundary=4 -no-pie

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char *name = 0;
    char *pass = 0;
    char num = 'A';
    while(1)
    {
        num = 'A';
        if(name) printf("name address: %x\nname: %s\n",name,name);
        if(pass) printf("pass address: %x\npass: %s\n",pass,pass);
        printf("1: Username\n");
        printf("2: Password\n");
        printf("3: Reset\n");
        printf("4: Login\n");
        printf("5: Exit\n");
        putchar('>');

        num=getchar();
        getchar();
        printf("\n");
 
        switch(num)
        {
            case '1':
                name = malloc(255*sizeof(char));
                printf("Insert Username: \n");
                scanf("%254s", name);
                if(strcmp(name,"root") == 0)
                {
                    printf("root not allowed.\n");
                    strcpy(name,"");
                }
                break;
            case '2':
                pass = malloc(255*sizeof(char));
                printf("Insert Password: \n");
                scanf("%254s", pass);
                break;
            case '3':
                printf("Freeing heap memory!\n");
                free(pass);
                free(name);
                break;
            case '4':
                printf("trying to log in...\n");
                if(strcmp(name,"root") == 0)
                {
                    printf("You just used after free!\n");
                    system("/bin/sh");
                    exit(0);
                }
                break;
            case '5':
                exit(0);
        }
    }
}
