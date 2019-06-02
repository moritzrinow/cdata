#ifndef _MAP_H
#define _MAP_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "array.h"
#include "types.h"

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

typedef struct map_s {
  alloc_t            alloc;
  array_t            entries;
  map_func_t         func;
	uint32_t					 num_elem;
} map_t;

typedef struct map_iterator_s {
	map_t											 *map;
	map_entry_t								 *current;
	uint32_t										index;
} map_iterator_t;

void map_entry_init(map_entry_t *entry);
void map_entry_destroy(map_t *map,
                       map_entry_t *entry);
void map_entry_destroy_recursive(map_t *map,
                                 map_entry_t *head);
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

typedef void (*map_foreach_key_func_t)(void *);
void map_foreach_key(map_t *map,
		     map_foreach_key_func_t action);

uint32_t map_key_hash_int8(void *);
uint32_t map_key_hash_int16(void *);
uint32_t map_key_hash_int32(void *);
uint32_t map_key_hash_int64(void *);

uint32_t map_key_hash_uint8(void *);
uint32_t map_key_hash_uint16(void *);
uint32_t map_key_hash_uint32(void *);
uint32_t map_key_hash_uint64(void *);

uint32_t map_key_hash_float32(void *);
uint32_t map_key_hash_float64(void *);

uint32_t map_key_hash_str(void *);

bool map_iterator_init(map_iterator_t *iterator,
											 map_t *map);
bool map_iterator_next(map_iterator_t *iterator);
bool map_iterator_first(map_iterator_t *iterator);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _MAP_H
