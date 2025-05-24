/* Program to demonstrate arithmetic right shift */
//gcc -m32 -g mul.c -o mul -fno-stack-protector -no-pie -mpreferred-stack-boundary=2 -fno-pic -z execstack
#include <stdio.h>
unsigned long long int mulBy12(unsigned long long int x) {return 12*x;}
int main(){
unsigned long long int a;
printf("Enter one int:");
scanf("%llu", &a);
printf("Result is:%llu\n", mulBy12(a));
return 0;
}

