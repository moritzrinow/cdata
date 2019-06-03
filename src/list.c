#include "list.h"

void list_init(list_t *list,
               list_func_t func)
{
  list->func = func;
  list->head = NULL;
  list->tail = NULL;
  list->num_elem = 0;
}

void list_push_front(list_t *list,
                     list_node_t *node)
{
  if(list->head == NULL){
    list->head = node;
    list->tail = node;
  }
  else {
    node->next = list->head;
    list->head = node;
  }
  list->num_elem++;
}

void list_push_tail(list_t *list,
                    list_node_t *node)
{
  if(list->head == NULL){
    list->head = node;
    list->tail = node;
  }
  else {
    list->tail->next = node;
    list->tail = node;
  }
  list->num_elem++;
}

list_node_t *list_pop_front(list_t *list)
{
  if(list->head == NULL){
    return NULL;
  }
  list_node_t *pop = list->head;
  if(pop->next == NULL){
    list->head = NULL;
    list->tail = NULL;
  }
  else {
    list->head = pop->next;
  }
  list->num_elem--;
  return pop;
}

void list_destroy(list_t *list)
{
  if(list->func.node_destroy){
    list_node_t *walker = list->head;
    while(walker){
      list_node_t *next = walker->next;
      list->func.node_destroy(walker);
      walker = next;
    }
  }
  list->head = NULL;
  list->tail = NULL;
  list->num_elem = 0;
}

void list_double_init(list_double_t *list,
                      list_double_func_t func)
{
  list->func = func;
  list->head = NULL;
  list->tail = NULL;
  list->num_elem = 0;
}

void list_double_push_front(list_double_t *list,
                            list_double_node_t *node)
{
  if(list->head == NULL){
    list->head = node;
    list->tail = node;
  }
  else {

  }
}

void list_double_push_tail(list_double_t *list,
                           list_double_node_t *node)
{

}

list_double_node_t *list_double_pop_front(list_double_t *list)
{

}

list_double_node_t *list_double_pop_tail(list_double_t *list)
{

}

void list_double_destroy(list_double_t *list)
{

}