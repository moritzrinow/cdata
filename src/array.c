#include <math.h>
#include <string.h>

#include "array.h"

#define array_space_left(array) (array->num_alloc - array->num_elem)

static inline bool array_valid_index(array_t *array,
                              uint32_t index)
{
  return index >= 0 && index < array->num_elem;
}

static inline uint32_t calculate_size_slack(uint32_t size)
{
  return (uint32_t)pow(ARRAY_GROWTH_FACTOR, (uint32_t)(log(size) / log(ARRAY_GROWTH_FACTOR)) + 1);
}

static bool array_resize_internal(array_t *array,
                                  uint32_t size,
                                  bool slack)
{
  if(size == 0){
    if(array->num_alloc > 0 && array->data){
      array->alloc.free(array->data);
      array->num_alloc = 0;
      array->num_elem = 0;
    }
    return true;
  }
  else{
    if(slack){
      size = calculate_size_slack(size);
    }
    if(size != array->num_alloc){
      if(array->num_alloc == 0){
        array->data = array->alloc.malloc(array->elem_size * size);
      }
      else{
        array->data = array->alloc.realloc(array->data, array->elem_size * size);
      }
      if(!array->data){
        return false;
      }
    }
  }
  array->num_alloc = size;
  if(size < array->num_elem){
    array->num_elem = array->num_alloc;
  }
  return true;
}

bool array_init(array_t *array,
                size_t elem_size,
                uint32_t num_alloc)
{
  array->alloc = alloc_std();
  array->data = NULL;
  array->elem_size = elem_size;
  array->num_alloc = 0;
  array->num_elem = 0;
  if(num_alloc > 0){
    array->data = array->alloc.malloc(elem_size * num_alloc);
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
    array->alloc.free(array->data);
    array->num_alloc = 0;
    array->num_elem = 0;
    array->data = NULL;
    array->elem_size = 0;
  }
}

void *array_push(array_t *array)
{
  uint32_t space_left = array_space_left(array);
  if(space_left < 1){
    if(!array_resize_internal(array, array->num_alloc + 1, true)){
      return NULL;
    }
  }
  uint8_t *data = (uint8_t *)array->data;
  return &data[array->elem_size * array->num_elem++];
}

bool array_push_value(array_t *array,
                      void *elem)
{
  void *next_elem = array_push(array);
  if(!next_elem){
    return false;
  }
  memcpy(next_elem, elem, array->elem_size);
  return true;
}

bool array_resize(array_t *array,
                  uint32_t size)
{
  return array_resize_internal(array, size, false);
}

void *array_get(array_t *array,
                uint32_t index)
{
  uint8_t *data = (uint8_t *)array->data;
  return &data[array->elem_size * index];
}

void *array_get_safe(array_t *array,
                     uint32_t index)
{
  if(!array_valid_index(array, index)){
    return NULL;
  }
  uint8_t *data = (uint8_t *)array->data;
  return &data[array->elem_size * index];
}
