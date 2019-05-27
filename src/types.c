#include "types.h"

alloc_t alloc_std = {
  &malloc,
  &free,
  &realloc
};
