#ifndef _MAP_H
#define _MAP_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "array.h"
#include "types.h"

typedef struct key_val_pair_s {
  void                       *key;
  void                       *val;
} key_val_pair_t;

typedef struct map_func_s {
  bool                  (*key_compare)(void *, void *);
  uint32_t              (*key_hash)(void *);
  void                  (*key_destroy)(void *);
  void                  (*val_destroy)(void *);
} map_func_t;

typedef struct map_entry_s {
  struct map_entry_s      *next;
  void                    *key;
  void                    *value;
} map_entry_t;

/*
  All keys and values pushed into this
  data structure are not copied. The map
  only keeps the pointers. Therefore
  allocating memory is on you. You can
  decide what will happend to the keys and values
  memory at map cleanup with setting the key_destroy
  and val_destroy function pointers in the map_func_t
  data structure.
*/
typedef struct map_s {
  alloc_t            alloc;
  array_t            entries;
  map_func_t         func;
  uint32_t           num_elem;
} map_t;

typedef struct map_iterator_s {
  map_t                      *map;
  map_entry_t                *current;
  uint32_t                    index;
} map_iterator_t;

bool map_init(map_t *map,
              uint32_t size,
              map_func_t func,
              bool std_alloc);
void map_destroy(map_t *map);
void *map_add_key(map_t *map,
                  void *key);
void *map_add_key_value(map_t *map,
                       void *key,
                       void *value);
void *map_lookup(map_t *map,
                 void *key);
bool map_contains_key(map_t *map,
                      void *key);
void map_remove(map_t *map,
                void *key);
bool map_rehash(map_t *map);
void map_merge(map_t *target,
               map_t *source);

typedef void (*map_foreach_key_func_t)(void *);
typedef void (*map_foreach_key_val_func_t)(key_val_pair_t pair);
void map_foreach_key(map_t *map,
                     map_foreach_key_func_t action);
void map_foreach_key_val(map_t *map,
                         map_foreach_key_val_func_t action);

bool map_iterator_init(map_iterator_t *iterator,
                       map_t *map);
bool map_iterator_next(map_iterator_t *iterator);
bool map_iterator_first(map_iterator_t *iterator);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _MAP_H
