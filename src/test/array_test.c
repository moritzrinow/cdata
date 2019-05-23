#include "cdata.h"
#include <stdio.h>

int main(int argc, char **argv)
{
  bool result;
  array_t array;

  result = array_init(&array, sizeof(int32_t), 12);
  if(!result){
    printf("Could not create array.\n");
    return 1;
  }
  printf("%s:%p\n", "Memory address of array data", array.data);
  printf("%s:%u\n", "Element size of array", array.elem_size);
  printf("%s:%u\n", "Number of elements in array", array.num_elem);
  printf("%s:%u\n", "Number of elements allocated in array", array.num_alloc);
  array_destroy(&array);

  return 0;
}
