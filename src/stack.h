#ifndef _STACK_H
#define _STACK_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "types.h"
#include "array.h"

/*
  All values pushed into this data structure
  get fully copied.
*/
typedef array_t stack_t;

bool stack_init(stack_t *stack,
                size_t elem_size,
                size_t size,
                bool std_alloc);
void stack_destroy(stack_t *stack);
void *stack_push(stack_t *stack);
bool stack_push_value(stack_t *stack,
                      void *elem);
bool stack_push_many(stack_t *stack,
                     uint32_t num,
                     void *elem);
bool stack_pop(stack_t *stack,
               void *out);

#define STACK_PUSH(stack, type, elem) \
  { \
    type val = elem; \
    bool pushed = stack_push_value(stack, &val); \
  }

#define STACK_PUSH_MANY(stack, type, num, elem) \
  { \
    type val = elem; \
    bool pushed = stack_push_many(stack, num, &val); \
  }

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _STACK_H