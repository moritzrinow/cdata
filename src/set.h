#ifndef _SET_H
#define _SET_H

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

typedef struct set_s {
  alloc_t            alloc;
  array_t            entries;
  set_func_t         func;
  uint32_t           num_elem;
} set_t;

void set_entry_init(set_entry_t *entry);
void set_entry_destroy(set_t *set,
                       set_entry_t *entry);
void set_entry_destroy_recursive(set_t *set,
                                 set_entry_t *head);

bool set_init(set_t *set,
              uint32_t size,
              set_func_t func,
              bool std_alloc);
void set_destroy(set_t *set);
bool set_add_elem(set_t *set,
                  void *elem);
bool set_lookup(set_t *set,
                void *elem);

#endif // _SET_H