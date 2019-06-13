#include "set.h"

static set_entry_t *set_lookup_entry(set_t *set,
                                     void *elem)
{
  set_entry_t *entry;
  uint32_t hash = set->func.elem_hash(elem);
  uint32_t index = hash % set->entries.num_elem;
  for(entry = ARRAY_GET_VAL(&set->entries, set_entry_t *, index); entry != NULL; entry = entry->next){
    if(set->func.elem_compare(entry->elem, elem)){
      return entry;
    }
  }
  return NULL;
}

void set_entry_init(set_entry_t *entry)
{
  entry->elem = NULL;
  entry->next = NULL;
}

void set_entry_destroy(set_t *set,
                       set_entry_t *entry)
{
  if(set->func.elem_destroy != NULL){
    set->func.elem_destroy(entry->elem);
  }
}

void set_entry_destroy_recursive(set_t *set,
                                 set_entry_t *head)
{
  set_entry_destroy(set, head);
  set_entry_t *walker = head->next;
  while(walker){
    set_entry_t *current = walker;
    walker = current->next;
    set_entry_destroy(set, current);
    set->alloc.free(current);
  }
}

bool set_init(set_t *set,
              uint32_t size,
              set_func_t func,
              bool std_alloc)
{
  if(std_alloc){
    set->alloc = alloc_std;
  }
  set->num_elem = 0;
  set->func = func;
  set->entries.alloc = set->alloc;
  if(!array_init(&set->entries, sizeof(set_entry_t *), size, false)){
    return false;
  }
  ARRAY_PUSH_MANY(&set->entries, set_entry_t *, size, NULL);
  return true;
}

void set_destroy(set_t *set)
{
  for(uint32_t i = 0; i < set->entries.num_elem; i++){
    set_entry_t *entry = ARRAY_GET_VAL(&set->entries, set_entry_t *, i);
    if(entry != NULL){
      set_entry_destroy_recursive(set, entry);
      set->alloc.free(entry);
    }
  }
  array_destroy(&set->entries);
  set->num_elem = 0;
}

bool set_add_elem(set_t *set,
                  void *elem)
{
  if(set->entries.num_elem < 1){
    return false;
  }

  set_entry_t *entry;
  uint32_t hash;
  if((entry = set_lookup_entry(set, elem)) != NULL){
    return false;
  }
  entry = (set_entry_t *)set->alloc.malloc(sizeof(set_entry_t));
  if(!entry){
    return false;
  }
  set_entry_init(entry);
  hash = set->func.elem_hash(elem);
  uint32_t index = hash % set->entries.num_elem;
  set_entry_t **head = ARRAY_GET(&set->entries, set_entry_t *, index);
  entry->next = *head;
  entry->elem = elem;
  *head = entry;
  set->num_elem++;
  return true;
}

bool set_lookup(set_t *set,
                void *elem)
{
  return set_lookup_entry(set, elem) != NULL;
}
