#include "hash.h"
#include "map.h"

static map_entry_t *map_lookup_entry(map_t *map,
                                     void *key)
{
  map_entry_t *entry;
  uint32_t hash = map->func.key_hash(key);
	uint32_t index = hash % map->entries.num_elem;
  for(entry = ARRAY_GET_VAL(&map->entries, map_entry_t *, index); entry != NULL; entry = entry->next){
    if(map->func.key_compare(entry->key, key)){
      return entry;
    }
  }
  return NULL;
}

void map_entry_init(map_entry_t *entry)
{
  entry->next = NULL;
  entry->key = NULL;
  entry->value = NULL;
}

void map_entry_destroy(map_t *map,
                       map_entry_t *entry)
{
  if(map->func.key_destroy != NULL){
    map->func.key_destroy(entry->key);
  }
  if(map->func.val_destroy != NULL){
    map->func.val_destroy(entry->value);
  }
}

void map_entry_destroy_recursive(map_t *map,
                                 map_entry_t *head)
{
  map_entry_destroy(map, head);
  map_entry_t *walker = head->next;
  while(walker){
    map_entry_t *current = walker;
    walker = current->next;
    map_entry_destroy(map, current);
    map->alloc.free(current);
  }
}

bool map_init(map_t *map,
              uint32_t size,
              map_func_t func,
              bool std_alloc)
{
  if(std_alloc){
    map->alloc = alloc_std;
  }
  map->func = func;
  map->entries.alloc = map->alloc;
  if(!array_init(&map->entries, sizeof(map_entry_t *), size, false)){
    return false;
  }
  ARRAY_PUSH_MANY(&map->entries, map_entry_t *, size, NULL);
  return true;
}

void map_destroy(map_t *map)
{
  for(uint32_t i = 0; i < map->entries.num_elem; i++){
    map_entry_t *entry = ARRAY_GET_VAL(&map->entries, map_entry_t *, i);
    if(entry != NULL){
      map_entry_destroy_recursive(map, entry);
      map->alloc.free(entry);
    }
  }
  array_destroy(&map->entries);
}

static map_entry_t *map_add_entry(map_t *map,
                                  void *key)
{
  if(map->entries.num_elem < 1) {
    return NULL;
  }

  map_entry_t *entry;
  uint32_t hash;
  if((entry = map_lookup_entry(map, key)) != NULL){
    return NULL;
  }
  entry = (map_entry_t *)map->alloc.malloc(sizeof(map_entry_t));
  if(!entry){
    return NULL;
  }
  map_entry_init(entry);
  hash = map->func.key_hash(key);
  uint32_t index = hash % map->entries.num_elem;
  map_entry_t **head = ARRAY_GET(&map->entries, map_entry_t *, index);
  entry->next = *head;
  *head = entry;
  return entry;
}

void *map_add_key(map_t *map,
                  void *key)
{
  map_entry_t *entry = map_add_entry(map, key);
  if(!entry){
    return NULL;
  }
	entry->key = key;
  return entry->value;
}

void *map_add_key_value(map_t *map,
                        void *key,
                        void *value)
{
  map_entry_t *entry = map_add_entry(map, key);
  if(!entry){
    return NULL;
  }
	entry->key = key;
  entry->value = value;
  return entry->value;
}

void *map_lookup(map_t *map,
                       void *key)
{
  map_entry_t *entry = map_lookup_entry(map, key);
  if(!entry){
    return NULL;
  }
  return entry->value;
}

bool map_contains_key(map_t *map,
                      void *key)
{
  map_entry_t *entry = map_lookup_entry(map, key);
  return entry != NULL;
}

void map_remove(map_t *map,
                void *key)
{
  if(map->entries.num_elem < 1) {
    return;
  }
  uint32_t index = map->func.key_hash(key) % map->entries.num_elem;
  map_entry_t **walker = &(ARRAY_GET_VAL(&map->entries, map_entry_t *, index));
  if(!walker){
    return;
  }
  while(*walker && !map->func.key_compare((*walker)->key, key)){
    walker = &(*walker)->next;
  }
  if(!(*walker)){
    return;
  }
  map_entry_t *to_remove = *walker;
  *walker = to_remove->next;
  map_entry_destroy(map, to_remove);
  map->alloc.free(to_remove);
}

void map_foreach_key(map_t *map,
										 map_foreach_key_func_t action)
{

}

uint32_t map_key_hash_int8(void *key)
{
  return hash_data((uint8_t *)key, sizeof(int8_t));
}

uint32_t map_key_hash_int16(void *key)
{
  return hash_data((uint8_t *)key, sizeof(int16_t));
}

uint32_t map_key_hash_int32(void *key)
{
  return hash_data((uint8_t *)key, sizeof(int32_t));
}

uint32_t map_key_hash_int64(void *key)
{
  return hash_data((uint8_t *)key, sizeof(int64_t));
}

uint32_t map_key_hash_uint8(void *key)
{
  return hash_data((uint8_t *)key, sizeof(uint8_t));
}

uint32_t map_key_hash_uint16(void *key)
{
  return hash_data((uint8_t *)key, sizeof(uint16_t));
}

uint32_t map_key_hash_uint32(void *key)
{
  return hash_data((uint8_t *)key, sizeof(uint32_t));
}

uint32_t map_key_hash_uint64(void *key)
{
  return hash_data((uint8_t *)key, sizeof(uint64_t));
}

uint32_t map_key_hash_float32(void *key)
{
  return hash_data((uint8_t *)key, sizeof(float));
}

uint32_t map_key_hash_float64(void *key)
{
  return hash_data((uint8_t *)key, sizeof(double));
}

uint32_t map_key_hash_str(void *key)
{
  return hash_str((uint8_t *)key);
}
