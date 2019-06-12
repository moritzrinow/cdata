#ifndef _TYPES_H
#define _TYPES_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct alloc_s {
  void              *(*malloc)(size_t);
  void               (*free)(void *);
  void              *(*realloc)(void *, size_t);
} alloc_t;

extern alloc_t alloc_std;

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _TYPES_H
