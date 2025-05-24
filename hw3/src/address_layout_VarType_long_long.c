
#include <stdio.h>
#include <malloc.h>

long long global_var_1 = 0;
long long global_var_2 = 0;

long long global_uninit_var_1;
long long global_uninit_var_2;

long long main()
{
  long long local_var_1 = 0;
  long long local_var_2 = 0;
  long long local_var_3 = 0;

  static long long static_var_1 = 0;
  static long long static_var_2 = 0;

  long long *ptr_1 = malloc(100);
  long long *ptr_2 = malloc(100);

  printf("Local long long var 1 address: %p\n", &local_var_1);
  printf("Local long long var 2 address: %p\n", &local_var_2);
  printf("Local long long var 3 address: %p\n", &local_var_3);

  printf("Heap long long var 1 address:%p\n", ptr_1);
  printf("Heap long long var 2 address:%p\n", ptr_2);

  printf("Global (uninit) long long var 1 address: %p\n", &global_uninit_var_1);
  printf("Global (uninit) long long var 2 address: %p\n", &global_uninit_var_2);

  printf("Static Local long long var 1 address: %p\n", &static_var_1);
  printf("Static Local long long var 2 address: %p\n", &static_var_2);

  printf("Global long long var 1 address: %p\n", &global_var_1);
  printf("Global long long var 2 address: %p\n", &global_var_2);

  return 0;
}

