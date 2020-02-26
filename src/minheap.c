#include "minheap.h"
#include <string.h>

#define LEFT_CHILD_INDEX(parent_index) (2 * parent_index + 1)
#define RIGHT_CHILD_INDEX(parent_index) (2 * parent_index + 2)
#define PARENT_INDEX(child_index) ((child_index - 1) / 2)

#define HAS_LEFT_CHILD(heap, index) (LEFT_CHILD_INDEX(index) < heap->num_elem)
#define HAS_RIGHT_CHILD(heap, index) (RIGHT_CHILD_INDEX(index) < heap->num_elem)
#define HAS_PARENT(index) (PARENT_INDEX(index) >= 0)

static inline void *left_child(minheap_t *heap,
                               uint32_t index)
{
  return array_get(&heap->array, LEFT_CHILD_INDEX(index));
}

static inline void *right_child(minheap_t *heap,
                                uint32_t index)
{
  return array_get(&heap->array, RIGHT_CHILD_INDEX(index));
}

static inline void *parent(minheap_t *heap,
                           uint32_t index)
{
  return array_get(&heap->array, PARENT_INDEX(index));
}

static void heapify_up(minheap_t *heap)
{
  if(heap->num_elem < 1){
    return;
  }
  uint32_t index = heap->num_elem - 1;
  while(HAS_PARENT(index) && (heap->func.elem_compare(parent(heap, index), array_get(&heap->array, index)) > 0)) {
    array_swap(&heap->array, PARENT_INDEX(index), index);
    index = PARENT_INDEX(index);
  }
}

static void heapify_down(minheap_t *heap)
{
  uint32_t index = 0;
  while(HAS_LEFT_CHILD(heap, index)){
    uint32_t small_child_index = LEFT_CHILD_INDEX(index);
    if(HAS_RIGHT_CHILD(heap, index) && (heap->func.elem_compare(right_child(heap, index), left_child(heap, index)) < 0)){
      small_child_index = RIGHT_CHILD_INDEX(index);
    }
    if(heap->func.elem_compare(array_get(&heap->array, index), array_get(&heap->array, small_child_index)) < 0){
      break;
    }
    else {
      array_swap(&heap->array, index, small_child_index);
    }
    index = small_child_index;
  }
}

bool minheap_init(minheap_t *heap,
                  minheap_func_t func,
                  size_t elem_size,
                  size_t size,
                  bool std_alloc)
{
  if(!array_init(&heap->array, elem_size, size, std_alloc)){
    return false;
  }
  heap->func = func;
  heap->num_elem = 0;
  return true;
}

void minheap_destroy(minheap_t *heap)
{
  array_destroy(&heap->array);
  heap->num_elem = 0;
}

bool minheap_peek(minheap_t *heap,
                  void *out)
{
  void *elem = array_get_safe(&heap->array, 0);
  if(!elem){
    return false;
  }
  memcpy(out, elem, heap->array.elem_size);
  return true;
}

bool minheap_poll(minheap_t *heap,
                  void *out)
{
  if(heap->num_elem < 1){
    return false;
  }
  void *elem = array_get_safe(&heap->array, 0);
  if(!elem){
    return false;
  }
  memcpy(out, elem, heap->array.elem_size);
  array_set(&heap->array, 0, array_get(&heap->array, heap->num_elem - 1));
  array_remove(&heap->array, heap->num_elem - 1);
  heap->num_elem--;
  heapify_down(heap);
  return true;
}

bool minheap_push(minheap_t *heap,
                  void *elem)
{
  if(!array_push_value(&heap->array, elem)){
    return false;
  }
  heap->num_elem++;
  heapify_up(heap);
  return true;
}

bool minheap_shrink(minheap_t *heap)
{
  return array_shrink(&heap->array);
}