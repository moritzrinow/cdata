#ifndef _MINHEAP_H
#define _MINHEAP_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "types.h"
#include "array.h"

typedef struct minheap_func_s {
  int32_t                   (*elem_compare)(void *, void *);
} minheap_func_t;

/*
  All values pushed into this data structure
  get fully copied.
*/
typedef struct minheap_s {
  minheap_func_t         func;
  array_t                array;
  uint32_t               num_elem;
} minheap_t;

bool minheap_init(minheap_t *heap,
                  minheap_func_t func,
                  size_t elem_size,
                  size_t size,
                  bool std_alloc);
void minheap_destroy(minheap_t *heap);
bool minheap_peek(minheap_t *heap,
                  void *out);
bool minheap_poll(minheap_t *heap,
                  void *out);
bool minheap_push(minheap_t *heap,
                  void *elem);
bool minheap_shrink(minheap_t *heap);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _MINHEAP_H