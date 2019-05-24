#ifndef _HASH_H
#define _HASH_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "types.h"

uint32_t hash_data(uint8_t *data,
                   size_t len);
uint32_t hash_str(uint8_t *str);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _HASH_H
