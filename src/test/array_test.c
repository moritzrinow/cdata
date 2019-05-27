#include "cdata.h"
#include <stdio.h>

int main(int argc, char **argv)
{
  bool result;
  array_t array;

  result = array_init(&array, sizeof(int32_t), 0, true);
  if(!result){
    printf("Could not create array.\n");
    return 1;
  }

  printf("%s:%p\n", "Memory address of array data", array.data);
  printf("%s:%u\n", "Element size of array", array.elem_size);
  printf("%s:%u\n", "Number of elements in array", array.num_elem);
  printf("%s:%u\n", "Number of elements allocated in array", array.num_alloc);

  ARRAY_PUSH(&array, int32_t, 1);
  ARRAY_PUSH(&array, int32_t, 2);
  ARRAY_PUSH(&array, int32_t, 3);
  ARRAY_PUSH(&array, int32_t, 4);
  ARRAY_PUSH(&array, int32_t, 5);
  ARRAY_PUSH(&array, int32_t, 6);
  ARRAY_PUSH(&array, int32_t, 7);
  ARRAY_PUSH(&array, int32_t, 8);
  ARRAY_PUSH(&array, int32_t, 9);

  for(int i = 0; i < array.num_elem; i++){
    int32_t val = ARRAY_GET_VAL(&array, int32_t, i);
    printf("%d\n", val);
  }

  printf("%s:%p\n", "Memory address of array data", array.data);
  printf("%s:%u\n", "Element size of array", array.elem_size);
  printf("%s:%u\n", "Number of elements in array", array.num_elem);
  printf("%s:%u\n", "Number of elements allocated in array", array.num_alloc);
  array_destroy(&array);

  return 0;
}
