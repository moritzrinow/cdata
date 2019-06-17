#include "set.h"

void set_entry_init(set_entry_t *entry);
void set_entry_destroy(set_t *set,
                       set_entry_t *entry);
void set_entry_destroy_recursive(set_t *set,
                                 set_entry_t *head);

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

void set_remove(set_t *set,
                void *elem)
{
  if(set->entries.num_elem < 1){
    return;
  }
  uint32_t index = set->func.elem_hash(elem) % set->entries.num_elem;
  set_entry_t **walker = &(ARRAY_GET_VAL(&set->entries, set_entry_t *, index));
  if(!walker){
    return;
  }
  set_entry_t *to_remove = *walker;
  *walker = to_remove->next;
  set_entry_destroy(set, to_remove);
  set->alloc.free(to_remove);
  set->num_elem--;
}

void set_merge(set_t *target,
               set_t *source)
{
  set_iterator_t iterator;
  for(set_iterator_init(&iterator, source); iterator.current != NULL; set_iterator_next(&iterator)){
    set_add_elem(target, iterator.current->elem);
  }
}

bool set_rehash(set_t *set)
{
  bool result;
  set_t copy;

  copy.alloc = set->alloc;
  result = set_init(&copy, set->num_elem, set->func, false);
  if(!result){
    return false;
  }
  set_merge(&copy, set);
  if(copy.num_elem != set->num_elem){
    return false;
  }
  set->func.elem_destroy = NULL;
  set_destroy(set);
  *set = copy;
  return true;
}

void set_foreach_elem(set_t *set,
                      set_foreach_elem_func_t action)
{
  set_iterator_t iterator;
  for(set_iterator_init(&iterator, set); iterator.current != NULL; set_iterator_next(&iterator)){
    action(iterator.current->elem);
  }
}

bool set_iterator_init(set_iterator_t *iterator,
                       set_t *set)
{
  iterator->set = set;
  iterator->index = 0;
  return set_iterator_first(iterator);
}

bool set_iterator_next(set_iterator_t *iterator)
{
  set_entry_t *entry = iterator->current;
  if(entry != NULL){
    if(entry->next != NULL){
      iterator->current = entry->next;
      return true;
    }
  }

  uint32_t *i = &iterator->index;
  for((*i)++; *i < iterator->set->entries.num_elem; (*i)++){
    entry = ARRAY_GET_VAL(&iterator->set->entries, set_entry_t *, *i);
    if(entry != NULL){
      iterator->current = entry;
      return true;
    }
  }
  iterator->current = NULL;
  return false;
}

bool set_iterator_first(set_iterator_t *iterator)
{
  set_entry_t *entry = ARRAY_GET_VAL(&iterator->set->entries, set_entry_t *, 0);
  if(entry != NULL){
    iterator->current = entry;
    return true;
  }
  for(uint32_t *i = &iterator->index; *i < iterator->set->entries.num_elem; (*i)++){
    entry = ARRAY_GET_VAL(&iterator->set->entries, set_entry_t *, *i);
    if(entry != NULL){
      iterator->current = entry;
      return true;
    }
  }
  return false;
}