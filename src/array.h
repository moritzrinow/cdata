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
                uint32_t num_alloc,
                bool std_alloc);
void array_destroy(array_t *array);
void *array_push(array_t *array);
bool array_push_value(array_t *array,
                      void *elem);
bool array_push_many(array_t *array,
                     uint32_t num,
                     void *elem);
void *array_insert(array_t *array,
                   uint32_t index);
bool array_insert_value(array_t *array,
                        uint32_t index,
                        void *elem);
void array_remove(array_t *array,
                  uint32_t index);
bool array_resize(array_t *array,
                  uint32_t size);
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

typedef bool (*array_compare_func_t)(void *, void *);
bool array_contains(array_t *array,
                    array_compare_func_t compare,
                    void *elem);
void *array_find_first(array_t *array,
                       array_compare_func_t compare,
                       void *elem);
void *array_find_last(array_t *array,
                      array_compare_func_t compare,
                      void *elem);

bool compare_std(void *elem1,
                 void *elem2,
                 size_t elem_size);
bool array_contains_std(array_t *array,
                        void *elem);
void *array_find_first_std(array_t *array,
                           void *elem);
void *array_find_last_std(array_t *array,
                          void *elem);

uint32_t array_count(array_t *array,
                     array_compare_func_t compare,
                     void *elem);
uint32_t array_count_std(array_t *array,
                         void* elem);

typedef void (*array_foreach_func_t)(void *);
void array_foreach(array_t *array,
                   array_foreach_func_t action);

#define ARRAY_PUSH(array, type, elem) \
( \
  { \
    type val = elem; \
    bool pushed = array_push_value(array, &val); \
    pushed; \
  } \
)

#define ARRAY_PUSH_MANY(array, type, num, elem) \
( \
  { \
    type val = elem; \
    bool pushed = array_push_many(array, num &val); \
    pushed; \
  } \
)

#define ARRAY_CONTAINS(array, type, compare_func, elem) \
( \
  { \
    type val = elem; \
    bool ret = array_contains(array, compare_func, &val); \
    ret; \
  } \
)

#define ARRAY_CONTAINS_STD(array, type, elem) \
( \
  { \
    type val = elem; \
    bool ret = array_contains_std(array, &val); \
    ret; \
  } \
)

#define ARRAY_FIND_FIRST(array, type, compare_func, elem) \
( \
  { \
    type val = elem; \
    void *found = array_find_first(array, compare_func, &val); \
    found; \
  } \
)

#define ARRAY_FIND_FIRST_STD(array, type, elem) \
( \
  { \
    type val = elem; \
    void *found = array_find_first_std(array, &val); \
    found; \
  } \
)

#define ARRAY_FIND_LAST(array, type, compare_func, elem) \
( \
  { \
    type val = elem; \
    void *found = array_find_last(array, compare_func, &val); \
    found; \
  } \
)

#define ARRAY_FIND_LAST_STD(array, type, elem) \
( \
  { \
    type val = elem; \
    void *found = array_find_last_std(array, &val); \
    found; \
  } \
)

#define ARRAY_COUNT(array, type, compare_func, elem) \
( \
  { \
    type val = elem; \
    uint32_t count = array_count(array, compare_func, &val); \
    count; \
  } \
)

#define ARRAY_COUNT_STD(array, type, elem) \
( \
  { \
    type val = elem; \
    uint32_t count = array_count_std(array, &val); \
    count; \
  } \
)

#define ARRAY_GET(array, type, index) ((type*)array_get(array, index))
#define ARRAY_GET_VAL(array, type, index) (*(type*)array_get(array, index))

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _ARRAY_H
