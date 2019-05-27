#ifndef _LIST_H
#define _LIST_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "types.h"

typedef struct list_node_s {
  void                    *data;
  struct list_node_s      *next;
} list_node_t;

typedef struct list_s {
  list_node_t        *head;
  uint32_t            num_elem;
} list_t;

void list_node_init(list_node_t *node);

void list_init(list_t *list);
void list_destroy(list_t *list);
list_node_t *list_add(list_t *list);
list_node_t *list_tail(list_t *list);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _LIST_H
