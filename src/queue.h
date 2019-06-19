#ifndef _QUEUE_H
#define _QUEUE_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "types.h"
#include "array.h"

typedef struct queue_s {
  array_t              array;
  uint32_t             front;
  uint32_t             rear;
  uint32_t             num_elem;
} queue_t;

bool queue_init(queue_t *queue,
                size_t elem_size,
                size_t size,
                bool std_alloc);
void queue_destroy(queue_t *queue);
bool queue_enqueue(queue_t *queue,
                   void *elem);
void *queue_dequeue(queue_t *queue);

#define QUEUE_ENQUEUE(queue, type, elem) \
  { \
    type val = elem; \
    bool queued = queue_enqueue(queue, &val); \
  }

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _QUEUE_H