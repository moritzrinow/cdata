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
} map_func_t;

typedef struct map_entry_s {
  map_entry_t             *next;
  void                    *key;
  void                    *value;
} map_entry_t;

typedef struct map_s {
  array_t            entries;
  map_func_t         func;
  size_t             key_size;
  size_t             val_size;
} map_t;

bool map_entry_init(map_entry_t *entry,
                    map_t *map);
void map_entry_destroy(map_entry_t *entry);
void map_entry_destroy_recursive(map_entry_t *head);

bool map_init(map_t *map,
              uint32_t size,
              map_func_t func,
              size_t key_size,
              size_t val_size);
void map_destroy(map_t *map);
void *map_add_key(map_t *map,
                  void *key);
bool map_add_key_value(map_t *map,
                        void *key,
                        void *value);
void *map_lookup(map_t *map,
                 void *key);
bool map_contains_key(map_t *map,
                      void *key);
void map_remove(map_t *map,
                void *key);

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

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _MAP_H
