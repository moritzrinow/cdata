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
                uint32_t num_alloc,
                bool std_alloc)
{
  if(std_alloc){
    array->alloc = alloc_std;
  }
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

bool array_push_many(array_t *array,
                     uint32_t num,
                     void *elem)
{
  if(num < 1){
    return false;
  }
  uint32_t space_left = array_space_left(array);
  if(space_left < num){
    if(!array_resize_internal(array, array->num_alloc + num, true)){
      return false;
    }
  }
  uint8_t *data = (uint8_t *)array->data;
  data = &data[array->num_elem * array->elem_size];
  for(uint32_t i = 0; i < num; i++){

    uint8_t *current = &data[i * array->elem_size];
    memcpy(current, elem, array->elem_size);
  }
	array->num_elem += num;
  return true;
}

bool array_push_zero(array_t *array,
                     uint32_t num)
{
  uint32_t space_left = array_space_left(array);
  if(space_left < num){
    if(!array_resize_internal(array, array->num_alloc + num, true)){
      return false;
    }
  }
  uint8_t *data = (uint8_t *)array->data;
  data = &data[array->num_elem * array->elem_size];
  memset(data, 0, array->elem_size * num);
  array->num_elem += num;
  return true;
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

void *array_insert(array_t *array,
                   uint32_t index)
{
  uint32_t space_left = array_space_left(array);
  if(space_left < 1){
    if(!array_resize_internal(array, array->num_alloc + 1, true)){
      return NULL;
    }
  }
  size_t elem_size = array->elem_size;
  uint8_t *data = (uint8_t *)array->data;
  uint8_t *src = &data[elem_size * index];
  uint8_t *dest = &data[elem_size * (index + 1)];
  memmove(dest, src, elem_size * (array->num_elem - 1 - index));
  array->num_elem++;
  return dest;
}

bool array_insert_value(array_t *array,
                        uint32_t index,
                        void *elem)
{
  void *inserted = array_insert(array, index);
  if(!inserted){
    return false;
  }
  memcpy(inserted, elem, array->elem_size);
  return true;
}

void array_remove(array_t *array,
                  uint32_t index)
{
  size_t elem_size = array->elem_size;
  uint8_t *data = (uint8_t *)array->data;
  uint8_t *src = &data[elem_size * (index + 1)];
  uint8_t *dest = &data[elem_size * index];
  memmove(dest, src, elem_size * (array->num_elem - (index + 1)));
  array->num_elem--;
}

bool array_resize(array_t *array,
                  uint32_t size)
{
  return array_resize_internal(array, size, false);
}

bool array_reserve(array_t *array,
                   size_t num)
{
  return array_resize_internal(array, array->num_alloc + num, false);
}

bool array_shrink(array_t *array)
{
  if(array->num_elem < array->num_alloc){
    return array_resize_internal(array, array->num_elem, false);
  }
  return true;
}

void *array_insert_safe(array_t *array,
                        uint32_t index)
{
  if(!array_valid_index(array, index)){
    return NULL;
  }
  return array_insert(array, index);
}

bool array_insert_value_safe(array_t *array,
                             uint32_t index,
                             void *elem)
{
  if(!array_valid_index(array, index)){
    return false;
  }
  return array_insert_value(array, index, elem);
}

bool array_remove_safe(array_t *array,
                       uint32_t index)
{
  if(!array_valid_index(array, index)){
    return false;
  }
  array_remove(array, index);
  return true;
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

void array_set(array_t *array,
               uint32_t index,
               void *elem)
{
  uint8_t *data = (uint8_t *)array->data;
  data = &data[array->elem_size * index];
  memcpy(data, elem, array->elem_size);
}

bool array_contains(array_t *array,
                    array_equal_func_t equal,
                    void *elem)
{
  uint32_t i;
  uint32_t num_elem = array->num_elem;

  for(i = 0; i < num_elem; i++){
    void *current = array_get(array, i);
    if(equal(current, elem)){
      return true;
    }
  }
  return false;
}

void *array_find_first(array_t *array,
                       array_equal_func_t equal,
                       void *elem)
{
  uint32_t i;
  uint32_t num_elem = array->num_elem;

  for(i = 0; i < num_elem; i++){
    void *current = array_get(array, i);
    if(equal(current, elem)){
      return current;
    }
  }
  return NULL;
}

void *array_find_last(array_t *array,
                      array_equal_func_t equal,
                      void *elem)
{
  int32_t i;
  uint32_t num_elem = array->num_elem;

  for(i = num_elem - 1; i >= 0; i--){
    void *current = array_get(array, i);
    if(equal(current, elem)){
      return current;
    }
  }
  return NULL;
}

bool equal_std(void *elem1,
                 void *elem2,
                 size_t elem_size)
{
  return memcmp(elem1, elem2, elem_size) == 0;
}

bool array_contains_std(array_t *array,
                        void *elem)
{
  uint32_t i;
  uint32_t num_elem = array->num_elem;

  for(i = 0; i < num_elem; i++){
    void *current = array_get(array, i);
    if(equal_std(current, elem, array->elem_size)){
      return true;
    }
  }
  return false;
}

void *array_find_first_std(array_t *array,
                           void *elem)
{
  uint32_t i;
  uint32_t num_elem = array->num_elem;

  for(i = 0; i < num_elem; i++){
    void *current = array_get(array, i);
    if(equal_std(current, elem, array->elem_size)){
      return current;
    }
  }
  return NULL;
}

void *array_find_last_std(array_t *array,
                          void *elem)
{
  int32_t i;
  uint32_t num_elem = array->num_elem;

  for(i = num_elem - 1; i >= 0; i--){
    void *current = array_get(array, i);
    if(equal_std(current, elem, array->elem_size)){
      return current;
    }
  }
  return NULL;
}

uint32_t array_count(array_t *array,
                     array_equal_func_t equal,
                     void *elem)
{
  uint32_t i;
  uint32_t num_elem = array->num_elem;
  uint32_t count = 0;

  for(i = 0;i < num_elem; i++){
    void *current = array_get(array, i);
    if(equal(current, elem)){
      count++;
    }
  }
  return count;
}

uint32_t array_count_std(array_t *array,
                         void* elem)
{
  uint32_t i;
  uint32_t num_elem = array->num_elem;
  uint32_t count = 0;

  for(i = 0;i < num_elem; i++){
    void *current = array_get(array, i);
    if(equal_std(current, elem, array->elem_size)){
      count++;
    }
  }
  return count;
}

void array_foreach(array_t *array,
                   array_foreach_func_t action)
{
  uint32_t i;
  uint32_t num_elem = array->num_elem;

  for(i = 0; i < num_elem; i++){
    void *current = array_get(array, i);
    action(current);
  }
}

int32_t compare_std(void *elem1,
                    void *elem2,
                    size_t elem_size)
{
  return memcmp(elem1, elem2, elem_size);
}

void array_swap(array_t *array,
                uint32_t index1,
                uint32_t index2)
{
  if(index1 == index2){
    return;
  }
  void *elem1 = array_get(array, index1);
  void *elem2 = array_get(array, index2);
  void *buffer = array->alloc.malloc(array->elem_size);
  memcpy(buffer, elem1, array->elem_size);
  memcpy(elem1, elem2, array->elem_size);
  memcpy(elem2, buffer, array->elem_size);
  array->alloc.free(buffer);
}

bool array_swap_safe(array_t *array,
                     uint32_t index1,
                     uint32_t index2)
{
  if(!array_valid_index(array, index1) || !array_valid_index(array, index2)){
    return false;
  }
  void* elem1 = array_get(array, index1);
  void* elem2 = array_get(array, index2);
  void* buffer = array->alloc.malloc(array->elem_size);
  memcpy(buffer, elem1, array->elem_size);
  memcpy(elem1, elem2, array->elem_size);
  memcpy(elem2, buffer, array->elem_size);
  array->alloc.free(buffer);
  return true;
}

bool array_iterator_init(array_iterator_t *iterator,
                         array_t *array)
{
  iterator->array = array;
  iterator->index = 0;
  iterator->current = NULL;
  return array_iterator_first(iterator);
}

bool array_iterator_next(array_iterator_t *iterator)
{
  if(!array_valid_index(iterator->array, iterator->index + 1)){
    iterator->current = NULL;
    return false;
  }
  iterator->current = array_get(iterator->array, iterator->index + 1);
  iterator->index++;
  return true;
}

bool array_iterator_prev(array_iterator_t *iterator)
{
  if(!array_valid_index(iterator->array, iterator->index - 1)){
    iterator->current = NULL;
    return false;
  }
  iterator->current = array_get(iterator->array, iterator->index - 1);
  iterator->index--;
  return true;
}

bool array_iterator_first(array_iterator_t *iterator)
{
  if(!array_valid_index(iterator->array, 0)){
    iterator->current = NULL;
    return false;
  }
  iterator->current = array_get(iterator->array, 0);
  return true;
}

bool array_iterator_last(array_iterator_t *iterator)
{
  if(iterator->array->num_elem < 1){
    iterator->current = NULL;
    return false;
  }
  iterator->current = array_get(iterator->array, iterator->array->num_elem - 1);
  iterator->index = iterator->array->num_elem - 1;
  return true;
}