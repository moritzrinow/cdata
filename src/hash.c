#include "hash.h"
#include "ctype.h"

#define hash_single(data, c) ((uint32_t)data * 31 + c)

uint32_t hash_data(uint8_t *data,
                   size_t len)
{
  uint32_t key = 0;
  for(uint32_t i = 0; i < len; i++){
    key = hash_single(key, tolower(data[i]));
  }
  return key;
}

uint32_t hash_int8(void *data)
{
  return hash_data((uint8_t *)data, sizeof(int8_t));
}

uint32_t hash_int16(void *data)
{
  return hash_data((uint8_t *)data, sizeof(int16_t));
}

uint32_t hash_int32(void *data)
{
  return hash_data((uint8_t *)data, sizeof(int32_t));
}

uint32_t hash_int64(void *data)
{
  return hash_data((uint8_t *)data, sizeof(int64_t));
}

uint32_t hash_uint8(void *data)
{
  return hash_data((uint8_t *)data, sizeof(uint8_t));
}

uint32_t hash_uint16(void *data)
{
  return hash_data((uint8_t *)data, sizeof(uint16_t));
}

uint32_t hash_uint32(void *data)
{
  return hash_data((uint8_t *)data, sizeof(uint32_t));
}

uint32_t hash_uint64(void *data)
{
  return hash_data((uint8_t *)data, sizeof(uint64_t));
}

uint32_t hash_float32(void *data)
{
  return hash_data((uint8_t *)data, sizeof(float));
}

uint32_t hash_float64(void *data)
{
  return hash_data((uint8_t *)data, sizeof(double));
}

uint32_t hash_str(void *data)
{
  uint8_t *str = (uint8_t *)data;
  int32_t c;
  uint32_t hash = 5381;

  while(c = (int32_t)*str++){
    hash = ((hash << 5) + hash) + c;
  }
  return hash;
}
