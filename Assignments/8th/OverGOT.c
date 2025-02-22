#include<stdio.h>

void main()
{
	char name[10];
	printf("Name : ");
	scanf("%s", name);
	system("chmod +x ${name}");
	printf("Hello %s.", name);
}
