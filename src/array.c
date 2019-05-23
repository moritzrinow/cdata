#include "array.h"

bool array_init(array_t *array,
                size_t elem_size,
                uint32_t num_alloc)
{
  array->data = NULL;
  array->elem_size = elem_size;
  array->num_alloc = 0;
  array->num_elem = 0;
  if(num_alloc > 0){
    array->data = malloc(elem_size * num_alloc);
    if(!array->data){
      return false;
    }
    array->num_alloc = num_alloc;
  }
  return true;
}

void array_destroy(array_t *array)
{
  if(array->num_alloc > 0 && array->data){
    free(array->data);
    array->num_alloc = 0;
    array->num_elem = 0;
    array->data = NULL;
    array->elem_size = 0;
  }
}
