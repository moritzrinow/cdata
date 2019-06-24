#include "stack.h"
#include <string.h>

bool stack_init(stack_t *stack,
                size_t elem_size,
                size_t size,
                bool std_alloc)
{
  return array_init(stack, elem_size, size, std_alloc);
}

void stack_destroy(stack_t *stack)
{
  array_destroy(stack);
}

void *stack_push(stack_t *stack)
{
  return array_push(stack);
}

bool stack_push_value(stack_t *stack,
                      void *elem)
{
  return array_push_value(stack, elem);
}

bool stack_push_many(stack_t *stack,
                     uint32_t num,
                     void *elem)
{
  return array_push_many(stack, num, elem);
}

bool stack_pop(stack_t *stack,
               void *out)
{
  void *elem = array_get_safe(stack, stack->num_elem - 1);
  if(!elem){
    return false;
  }
  memcpy(out, elem, stack->elem_size);
  stack->num_elem--;
  return true;
}