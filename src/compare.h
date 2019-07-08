#ifndef _CDATA_COMPARE_H
#define _CDATA_COMPARE_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "types.h"

int32_t compare_int8(void *elem1, void *elem2);
int32_t compare_int16(void *elem1, void *elem2);
int32_t compare_int32(void *elem1, void *elem2);
int32_t compare_int64(void *elem1, void *elem2);

int32_t compare_uint8(void *elem1, void *elem2);
int32_t compare_uint16(void *elem1, void *elem2);
int32_t compare_uint32(void *elem1, void *elem2);
int32_t compare_uint64(void *elem1, void *elem2);

int32_t compare_float32(void *elem1, void *elem2);
int32_t compare_float64(void *elem1, void *elem2);

int32_t compare_str(void *str1, void *str2);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _CDATA_COMPARE_H
