#ifndef _CDATA_LIST_H
#define _CDATA_LIST_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "types.h"

struct list_node_s;
typedef struct list_node_s list_node_t;

typedef struct list_func_s {
  void                   (*node_destroy)(list_node_t *);
} list_func_t;

typedef struct list_node_s {
  void                    *data;
  list_node_t             *next;
} list_node_t;

typedef struct list_s {
  list_node_t        *head;
  list_node_t        *tail;
  uint32_t            num_elem;
  list_func_t         func;
} list_t;

void list_init(list_t *list,
               list_func_t func);
void list_push_front(list_t *list,
                     list_node_t *node);
void list_push_tail(list_t *list,
                    list_node_t *node);
list_node_t *list_pop_front(list_t *list);
void list_destroy(list_t *list);

struct list_double_node_s;
typedef struct list_double_node_s list_double_node_t;

typedef struct list_double_func_s {
  void                          (*node_destroy)(list_double_node_t *);
} list_double_func_t;

typedef struct list_double_node_s {
  void                           *data;
  list_double_node_t             *next;
  list_double_node_t             *prev;
} list_double_node_t;

typedef struct list_double_s {
  list_double_node_t        *head;
  list_double_node_t        *tail;
  uint32_t                   num_elem;
  list_double_func_t         func;
} list_double_t;

void list_double_init(list_double_t *list,
                      list_double_func_t func);
void list_double_push_front(list_double_t *list,
                            list_double_node_t *node);
void list_double_push_tail(list_double_t *list,
                           list_double_node_t *node);
list_double_node_t *list_double_pop_front(list_double_t *list);
list_double_node_t *list_double_pop_tail(list_double_t *list);
void list_double_destroy(list_double_t *list);


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _CDATA_LIST_H
