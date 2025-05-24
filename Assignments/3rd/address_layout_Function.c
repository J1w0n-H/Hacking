
#include <stdio.h>
#include <malloc.h>

int global_var_1 = 0;
int global_var_2 = 0;

int global_uninit_var_1;
int global_uninit_var_2;

void parameterAnalysis(int global_par_1, int global_par_2, int global_uninit_par_1, int global_uninit_par_2, int local_par_1, int local_par_2, int *ptr_par_1, int *ptr_par_2, int static_par_1, int static_par_2);



int main()
{
  int local_var_1 = 0;
  int local_var_2 = 0;

  int *ptr_1 = malloc(100);
  int *ptr_2 = malloc(100);
  
  static int static_var_1 = 0;
  static int static_var_2 = 0;

  printf("Local var 1 address: %p\n", &local_var_1);
  printf("Local var 2 address: %p\n", &local_var_2);

  printf("Heap var 1 address:%p\n", ptr_1);
  printf("Heap var 2 address:%p\n", ptr_2);

  printf("Global (uninit) var 1 address: %p\n", &global_uninit_var_1);
  printf("Global (uninit) var 2 address: %p\n", &global_uninit_var_2);

  printf("Static Local var 1 address: %p\n", &static_var_1);
  printf("Static Local var 2 address: %p\n", &static_var_2);

  printf("Global var 1 address: %p\n", &global_var_1);
  printf("Global var 2 address: %p\n", &global_var_2);

  parameterAnalysis(global_var_1, global_var_2, global_uninit_var_1, global_uninit_var_2, local_var_1, local_var_2, ptr_1, ptr_2, static_var_1, static_var_2);

  return 0;
}


void parameterAnalysis(int global_par_1, int global_par_2, int global_uninit_par_1, int global_uninit_par_2, int local_par_1, int local_par_2, int *ptr_par_1, int *ptr_par_2, int static_par_1, int static_par_2){
  printf("\nParameters\n");
  //Print the variables as parameters
  printf("Local par 1 address: %p\n", &local_par_1);
  printf("Local par 2 address: %p\n", &local_par_2);
 
  printf("Heap par 1 address: %p\n", ptr_par_1);
  printf("Heap par 2 address: %p\n", ptr_par_2);
 
  printf("Global (uninit) par 1 address: %p\n", &global_uninit_par_1);
  printf("Global (uninit) par 2 address: %p\n", &global_uninit_par_2);

  printf("Static par 1 address: %p\n", &static_par_1);
  printf("Static par 2 address: %p\n", &static_par_2);

  printf("Global par 1 address: %p\n", &global_par_1);
  printf("Global par 2 address: %p\n", &global_par_2);
}

