#ifndef _CDATA_SET_H
#define _CDATA_SET_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "array.h"
#include "types.h"
#include "hash.h"

typedef struct set_func_s {
  uint32_t              (*elem_hash)(void *);
  bool                  (*elem_compare)(void *, void *);
  void                  (*elem_destroy)(void *);
} set_func_t;

typedef struct set_entry_s {
  struct set_entry_s      *next;
  void                    *elem;
} set_entry_t;

/*
  All values pushed into this
  data structure are not copied. The set
  only keeps the pointers. Therefore
  allocating memory is on you. You can
  decide what will happend to the values
  memory at set cleanup with setting the
  elem_destroy function pointers in the set_func_t
  data structure.
*/
typedef struct set_s {
  alloc_t            alloc;
  array_t            entries;
  set_func_t         func;
  uint32_t           num_elem;
} set_t;

typedef struct set_iterator_s {
  set_t                      *set;
  set_entry_t                *current;
  uint32_t                    index;
} set_iterator_t;

bool set_init(set_t *set,
              uint32_t size,
              set_func_t func,
              bool std_alloc);
void set_destroy(set_t *set);
bool set_add_elem(set_t *set,
                  void *elem);
bool set_lookup(set_t *set,
                void *elem);
void set_remove(set_t *set,
                void *elem);
void set_merge(set_t *target,
               set_t *source);
bool set_rehash(set_t *set);

typedef void (*set_foreach_elem_func_t)(void *);
void set_foreach_elem(set_t *set,
                      set_foreach_elem_func_t action);

bool set_iterator_init(set_iterator_t *iterator,
                       set_t *set);
bool set_iterator_next(set_iterator_t *iterator);
bool set_iterator_first(set_iterator_t *iterator);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _CDATA_SET_H
