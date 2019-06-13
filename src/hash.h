#ifndef _HASH_H
#define _HASH_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "types.h"

uint32_t hash_data(uint8_t *data,
                   size_t len);
uint32_t hash_int8(void *);
uint32_t hash_int16(void *);
uint32_t hash_int32(void *);
uint32_t hash_int64(void *);

uint32_t hash_uint8(void *);
uint32_t hash_uint16(void *);
uint32_t hash_uint32(void *);
uint32_t hash_uint64(void *);

uint32_t hash_float32(void *);
uint32_t hash_float64(void *);

uint32_t hash_str(void *);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _HASH_H
