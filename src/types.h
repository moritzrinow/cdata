#ifndef _TYPES_H
#define _TYPES_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct alloc_s {
  void *             (*malloc)(size_t);
  void               (*free)(void *);
  void *             (*realloc)(void *, size_t);
} alloc_t;

alloc_t alloc_std();

#endif // _TYPES_H
