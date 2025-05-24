
#include <stdio.h>
#include <malloc.h>

float global_var_1 = 0;
float global_var_2 = 0;

float global_uninit_var_1;
float global_uninit_var_2;

float main()
{
  float local_var_1 = 0;
  float local_var_2 = 0;
  float local_var_3 = 0;

  static float static_var_1 = 0;
  static float static_var_2 = 0;

  float *ptr_1 = malloc(100);
  float *ptr_2 = malloc(100);

  printf("Local float var 1 address: %p\n", &local_var_1);
  printf("Local float var 2 address: %p\n", &local_var_2);
  printf("Local float var 3 address: %p\n", &local_var_3);

  printf("Heap float var 1 address:%p\n", ptr_1);
  printf("Heap float var 2 address:%p\n", ptr_2);

  printf("Global (uninit) float var 1 address: %p\n", &global_uninit_var_1);
  printf("Global (uninit) float var 2 address: %p\n", &global_uninit_var_2);

  printf("Static Local float var 1 address: %p\n", &static_var_1);
  printf("Static Local float var 2 address: %p\n", &static_var_2);

  printf("Global float var 1 address: %p\n", &global_var_1);
  printf("Global float var 2 address: %p\n", &global_var_2);

  return 0;
}

