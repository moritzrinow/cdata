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
int32_t compare_str_ci(void *str1, void *str2);
int32_t compare_ptr(void *ptr1, void *ptr2);

bool equal_int8(void *elem1, void *elem2);
bool equal_int16(void *elem1, void *elem2);
bool equal_int32(void *elem1, void *elem2);
bool equal_int64(void *elem1, void *elem2);
bool equal_uint8(void *elem1, void *elem2);
bool equal_uint16(void *elem1, void *elem2);
bool equal_uint32(void *elem1, void *elem2);
bool equal_uint64(void *elem1, void *elem2);
bool equal_float32(void *elem1, void *elem2);
bool equal_float64(void *elem1, void *elem2);
bool equal_str(void *str1, void *str2);
bool equal_str_ci(void *str1, void *str2);
bool equal_ptr(void *ptr1, void *ptr2);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _CDATA_COMPARE_H
