
#include <stdio.h>
#include <malloc.h>

int global_var_1 = 0;

int global_uninit_var_1;

int main()
{
  int local_var_1 = 0;

  int *ptr_1 = malloc(100);


  static int static_var_1 = 0;
  printf("Local var 1 address: %p\n", &local_var_1);

  printf("Heap var 1 address:%p\n", ptr_1);

  printf("Global (uninit) var 1 address: %p\n", &global_uninit_var_1);

  printf("Static Local var 1 address: %p\n", &static_var_1);

  printf("Global var 1 address: %p\n", &global_var_1);

  return 0;
}

