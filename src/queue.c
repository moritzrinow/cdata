#include "queue.h"
#include <string.h>

#define QUEUE_IS_FULL(queue) (queue->num_elem == queue->array.num_elem)
#define QUEUE_IS_EMPTY(queue) (queue->num_elem == 0)

bool queue_init(queue_t *queue,
                size_t elem_size,
                size_t size,
                bool std_alloc)
{
  if(size < 1){
    return false;
  }
  if(!array_init(&queue->array, elem_size, size, std_alloc)){
    return false;
  }
  if(!array_push_zero(&queue->array, size)){
    queue_destroy(queue);
    return false;
  }
  queue->num_elem = 0;
  queue->front = 0;
  queue->rear = size - 1;
  return true;
}

void queue_destroy(queue_t *queue)
{
  array_destroy(&queue->array);
  queue->front = 0;
  queue->rear = 0;
  queue->num_elem = 0;
}

bool queue_enqueue(queue_t *queue,
                   void *elem)
{
  if(QUEUE_IS_FULL(queue)){
    return false;
  }
  queue->rear = (queue->rear + 1) % queue->array.num_elem;
  void *dest = array_get(&queue->array, queue->rear);
  memcpy(dest, elem, queue->array.elem_size);
  queue->num_elem++;
  return true;
}

bool queue_dequeue(queue_t *queue,
                   void **out)
{
  if(QUEUE_IS_EMPTY(queue)){
    return false;
  }
  void *elem = array_get(&queue->array, queue->front);
  *out = elem;
  queue->front = (queue->front + 1) % queue->array.num_elem;
  queue->num_elem--;
  return true;
}