#include "hash.h"
#include "map.h"

static map_entry_t *map_lookup_entry(map_t *map,
                                     void *key)
{
  map_entry_t *entry;
  uint32_t hash = map->func.key_hash(key);
  for(entry = ARRAY_GET_VAL(&map->entries, map_entry_t *, hash); entry != NULL; entry = entry->next){
    if(map->func.key_compare(entry->key, key)){
      return entry;
    }
  }
  return NULL;
}

bool map_entry_init(map_entry_t *entry,
                    map_t *map)
{
  entry->next = NULL;
  key = malloc(map->key_size);
  value = malloc(map->val_size);
  if(!key || !value){
    return false;
  }
  return true;
}

void map_entry_destroy(map_entry_t *entry)
{
  free(entry->key);
  free(entry->value);
}

void map_entry_destroy_recursive(map_entry_t *head)
{
  map_entry_destroy(head);
  map_entry_t *walker = head->next;
  while(walker){
    map_entry_t *current = walker;
    walker = current->next;
    map_entry_destroy(current);
    free(current);
  }
}

bool map_init(map_t *map,
              uint32_t size,
              map_func_t func,
              size_t key_size,
              size_t val_size)
{
  map->func = func;
  map->key_size = key_size;
  map->val_size = val_size;
  if(!array_init(&map->entries, sizeof(map_entry_t *), size){
    return false;
  }
  ARRAY_PUSH_MANY(&map->enties, map_entry_t *, size, NULL);

  return true;
}

void map_destroy(map_t *map)
{
  for(uint32_t i = 0; i < map->entries.num_elem; i++){
    map_entry_t *entry = ARRAY_GET_VAL(&map->entries, map_entry_t *, i);
    if(entry != NULL){
      map_entry_destroy_recursive(entry);
      free(entry);
    }
  }
  array_destroy(&map->entries);
}

void *map_add_key(map_t *map,
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
  entry = (map_entry_t *)malloc(sizeof(map_entry_t));
  if(!entry){
    return NULL;
  }
  if(!map_entry_init(entry, map)){
    free(entry);
    return NULL;
  }
  hash = map->func.hash_key(key);
  uint32_t index = hash % map->entries.num_elem;
  map_entry_t **head = ARRAY_GET(&map->entries, map_entry_t *, index);
  entry->next = *head;
  *head = entry;
  return entry->value;
}

void *map_add_key_value(map_t *map,
                        void *key,
                        void *value)
{
  void *entry_val = map_add_key(map, key);
  if(!entry_val){
    return false;
  }
  memcpy(entry_val, value, map->val_size);
  return true;
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
  uint32_t index = map->func.hash_key(key) % map->num_elem;
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
  map_entry_destroy(to_remove);
  free(to_remove);
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
