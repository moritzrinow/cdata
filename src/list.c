#include "list.h"

void list_node_init(list_node_t *node)
{
  node->data = NULL;
  node->next = NULL;
}

void list_init(list_t *list)
{
  list->head = NULL;
  list->num_elem = 0;
}

void list_destroy(list_t *list)
{

  list->num_elem = 0;
}

list_node_t *list_add(list_t *list)
{
  
}
