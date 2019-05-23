#include "types.h"

alloc_t alloc_std()
{
  alloc_t alloc;
  alloc.malloc = &malloc;
  alloc.free = &free;
  alloc.realloc = &realloc;
  return alloc;
}
