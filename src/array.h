#ifndef _ARRAY_H
#define _ARRAY_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifndef ARRAY_GROWTH_FACTOR
#define ARRAY_GROWTH_FACTOR 1.5
#endif // ARRAY_GROWTH_FACTOR

#include "types.h"

typedef struct array_s {
  alloc_t              alloc;
  void                *data;
  size_t               elem_size;
  uint32_t             num_elem;
  uint32_t             num_alloc;
} array_t;

bool array_init(array_t *array,
                size_t elem_size,
                uint32_t num_alloc);
void array_destroy(array_t *array);
void *array_push(array_t *array);
bool array_push_value(array_t *array,
                      void *elem);
bool array_resize(array_t *array,
                  uint32_t size);
void *array_get(array_t *array,
                uint32_t index);
void *array_get_safe(array_t *array,
                     uint32_t index);

#define ARRAY_PUSH(array, type, elem) \
do { \
  type val = elem; \
  array_push_value(array, &val); \
} while(0);

#define ARRAY_GET(array, type, index) ((type*)array_get(array, index))
#define ARRAY_GET_VAL(array, type, index) (*(type*)array_get(array, index))

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _ARRAY_H
