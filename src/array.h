#ifndef _ARRAY_H
#define _ARRAY_H

#include <types.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct array_s {
  void                *data;
  size_t               elem_size;
  uint32_t             num_elem;
  uint32_t             num_alloc;
} array_t;

bool array_init(array_t *array,
                size_t elem_size,
                uint32_t num_alloc);
void array_destroy(array_t *array);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _ARRAY_H
