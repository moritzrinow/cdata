#include "hash.h"
#include "ctype.h"

#define hash_single(key, c) ((uint32_t)key * 31 + c)

uint32_t hash_data(uint8_t *data,
                   size_t len)
{
  uint32_t key = 0;
  for(uint32_t i = 0; i < len; i++){
    key = hash_single(key, tolower(data[i]));
  }
  return key;
}

uint32_t hash_str(uint8 *str)
{
  int32_t c;
  uint32_t hash = 5381;

  while(c = (int32_t)*str++){
    hash = ((hash << 5) + hash) + c;
  }
  return hash;
}
