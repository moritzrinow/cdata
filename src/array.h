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

typedef struct array_iterator_s {
  array_t                      *array;
  void                         *current;
  uint32_t                      index;
} array_iterator_t;

bool array_init(array_t *array,
                size_t elem_size,
                uint32_t num_alloc,
                bool std_alloc);
void array_destroy(array_t *array);
void *array_push(array_t *array);
bool array_push_value(array_t *array,
                      void *elem);
bool array_push_many(array_t *array,
                     uint32_t num,
                     void *elem);
bool array_push_zero(array_t *array,
                     uint32_t num);
void *array_insert(array_t *array,
                   uint32_t index);
bool array_insert_value(array_t *array,
                        uint32_t index,
                        void *elem);
void array_remove(array_t *array,
                  uint32_t index);
bool array_resize(array_t *array,
                  uint32_t size);
bool array_reserve(array_t *array,
                   size_t num);
bool array_shrink(array_t *array);
void *array_insert_safe(array_t *array,
                        uint32_t index);
bool array_insert_value_safe(array_t *array,
                             uint32_t index,
                             void *elem);
bool array_remove_safe(array_t *array,
                       uint32_t index);
void *array_get(array_t *array,
                uint32_t index);
void *array_get_safe(array_t *array,
                     uint32_t index);

typedef bool (*array_equal_func_t)(void *, void *);
bool array_contains(array_t *array,
                    array_equal_func_t equal,
                    void *elem);
void *array_find_first(array_t *array,
                       array_equal_func_t equal,
                       void *elem);
void *array_find_last(array_t *array,
                      array_equal_func_t equal,
                      void *elem);

bool equal_std(void *elem1,
               void *elem2,
               size_t elem_size);
bool array_contains_std(array_t *array,
                        void *elem);
void *array_find_first_std(array_t *array,
                           void *elem);
void *array_find_last_std(array_t *array,
                          void *elem);

uint32_t array_count(array_t *array,
                     array_equal_func_t equal,
                     void *elem);
uint32_t array_count_std(array_t *array,
                         void* elem);

typedef void (*array_foreach_func_t)(void *);
void array_foreach(array_t *array,
                   array_foreach_func_t action);

typedef int32_t (*array_compare_func_t)(void *, void *);
int32_t compare_std(void *elem1,
                    void *elem2,
                    size_t elem_size);

void array_swap(array_t *array,
                uint32_t index1,
                uint32_t index2);
bool array_swap_safe(array_t *array,
                     uint32_t index1,
                     uint32_t index2);

bool array_iterator_init(array_iterator_t *iterator,
                         array_t *array);
bool array_iterator_next(array_iterator_t *iterator);
bool array_iterator_prev(array_iterator_t *iterator);
bool array_iterator_first(array_iterator_t *iterator);
bool array_iterator_last(array_iterator_t *iterator);

#define ARRAY_PUSH(array, type, elem) \
  { \
    type val = elem; \
    bool pushed = array_push_value(array, &val); \
  }

#define ARRAY_PUSH_MANY(array, type, num, elem) \
  { \
    type val = elem; \
    bool pushed = array_push_many(array, num, &val); \
  }

#define ARRAY_GET(array, type, index) ((type*)array_get(array, index))
#define ARRAY_GET_VAL(array, type, index) (*(type*)array_get(array, index))

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _ARRAY_H
