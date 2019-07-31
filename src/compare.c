#include "compare.h"
#include <string.h>

int32_t compare_int8(void *elem1, void *elem2)
{
  int8_t *ptr1 = (int8_t *)elem1;
  int8_t *ptr2 = (int8_t *)elem2;
  if(*ptr1 < *ptr2){
    return -1;
  }
  if(*ptr1 == *ptr2){
    return 0;
  }
  if(*ptr1 > *ptr2){
    return 1;
  }
}

int32_t compare_int16(void *elem1, void *elem2)
{
  int16_t *ptr1 = (int16_t *)elem1;
  int16_t *ptr2 = (int16_t *)elem2;
  if(*ptr1 < *ptr2){
    return -1;
  }
  if(*ptr1 == *ptr2){
    return 0;
  }
  if(*ptr1 > *ptr2){
    return 1;
  }
}

int32_t compare_int32(void *elem1, void *elem2)
{
  int32_t *ptr1 = (int32_t *)elem1;
  int32_t *ptr2 = (int32_t *)elem2;
  if(*ptr1 < *ptr2){
    return -1;
  }
  if(*ptr1 == *ptr2){
    return 0;
  }
  if(*ptr1 > *ptr2){
    return 1;
  }
}

int32_t compare_int64(void *elem1, void *elem2)
{
  int64_t *ptr1 = (int64_t *)elem1;
  int64_t *ptr2 = (int64_t *)elem2;
  if(*ptr1 < *ptr2){
    return -1;
  }
  if(*ptr1 == *ptr2){
    return 0;
  }
  if(*ptr1 > *ptr2){
    return 1;
  }
}

int32_t compare_uint8(void *elem1, void *elem2)
{
  uint8_t *ptr1 = (uint8_t *)elem1;
  uint8_t *ptr2 = (uint8_t *)elem2;
  if(*ptr1 < *ptr2){
    return -1;
  }
  if(*ptr1 == *ptr2){
    return 0;
  }
  if(*ptr1 > *ptr2){
    return 1;
  }
}

int32_t compare_uint16(void *elem1, void *elem2)
{
  uint16_t *ptr1 = (uint16_t *)elem1;
  uint16_t *ptr2 = (uint16_t *)elem2;
  if(*ptr1 < *ptr2){
    return -1;
  }
  if(*ptr1 == *ptr2){
    return 0;
  }
  if(*ptr1 > *ptr2){
    return 1;
  }
}

int32_t compare_uint32(void *elem1, void *elem2)
{
  uint32_t *ptr1 = (uint32_t *)elem1;
  uint32_t *ptr2 = (uint32_t *)elem2;
  if(*ptr1 < *ptr2){
    return -1;
  }
  if(*ptr1 == *ptr2){
    return 0;
  }
  if(*ptr1 > *ptr2){
    return 1;
  }
}

int32_t compare_uint64(void *elem1, void *elem2)
{
  uint64_t *ptr1 = (uint64_t *)elem1;
  uint64_t *ptr2 = (uint64_t *)elem2;
  if(*ptr1 < *ptr2){
    return -1;
  }
  if(*ptr1 == *ptr2){
    return 0;
  }
  if(*ptr1 > *ptr2){
    return 1;
  }
}

int32_t compare_float32(void *elem1, void *elem2)
{
  float *ptr1 = (float *)elem1;
  float *ptr2 = (float *)elem2;
  if(*ptr1 < *ptr2){
    return -1;
  }
  if(*ptr1 == *ptr2){
    return 0;
  }
  if(*ptr1 > *ptr2){
    return 1;
  }
}

int32_t compare_float64(void *elem1, void *elem2)
{
  double *ptr1 = (double *)elem1;
  double *ptr2 = (double *)elem2;
  if(*ptr1 < *ptr2){
    return -1;
  }
  if(*ptr1 == *ptr2){
    return 0;
  }
  if(*ptr1 > *ptr2){
    return 1;
  }
}

int32_t compare_str(void *str1, void *str2)
{
  return strcmp((const char *)str1, (const char *)str2);
}

int32_t compare_str_ci(void *str1, void *str2)
{
  char *ptr1 = (char *)str1;
  char *ptr2 = (char *)str2;
  for (;; ptr1++, ptr2++) {
        int d = tolower((unsigned char)*ptr1) - tolower((unsigned char)*ptr2);
        if (d != 0 || !*ptr1)
            return d;
    }
}

int32_t compare_ptr(void *ptr1, void *ptr2)
{
  if(ptr1 < ptr2){
    return -1;
  }
  if(ptr1 == ptr2){
    return 0;
  }
  if(ptr1 > ptr2){
    return 1;
  }
}

bool equal_int8(void *elem1, void *elem2)
{
  int8_t *ptr1 = (int8_t *)elem1;
  int8_t *ptr2 = (int8_t *)elem2;
  return *ptr1 == *ptr2;
}

bool equal_int16(void *elem1, void *elem2)
{
  int16_t *ptr1 = (int16_t *)elem1;
  int16_t *ptr2 = (int16_t *)elem2;
  return *ptr1 == *ptr2;
}

bool equal_int32(void *elem1, void *elem2)
{
  int32_t *ptr1 = (int32_t *)elem1;
  int32_t *ptr2 = (int32_t *)elem2;
  return *ptr1 == *ptr2;
}

bool equal_int64(void *elem1, void *elem2)
{
  int64_t *ptr1 = (int64_t *)elem1;
  int64_t *ptr2 = (int64_t *)elem2;
  return *ptr1 == *ptr2;
}

bool equal_uint8(void *elem1, void *elem2)
{
  uint8_t *ptr1 = (uint8_t *)elem1;
  uint8_t *ptr2 = (uint8_t *)elem2;
  return *ptr1 == *ptr2;
}

bool equal_uint16(void *elem1, void *elem2)
{
  uint16_t *ptr1 = (uint16_t *)elem1;
  uint16_t *ptr2 = (uint16_t *)elem2;
  return *ptr1 == *ptr2;
}

bool equal_uint32(void *elem1, void *elem2)
{
  uint32_t *ptr1 = (uint32_t *)elem1;
  uint32_t *ptr2 = (uint32_t *)elem2;
  return *ptr1 == *ptr2;
}

bool equal_uint64(void *elem1, void *elem2)
{
  uint64_t *ptr1 = (uint64_t *)elem1;
  uint64_t *ptr2 = (uint64_t *)elem2;
  return *ptr1 == *ptr2;
}

bool equal_float32(void *elem1, void *elem2)
{
  float *ptr1 = (float *)elem1;
  float *ptr2 = (float *)elem2;
  return *ptr1 == *ptr2;
}

bool equal_float64(void *elem1, void *elem2)
{
  double *ptr1 = (double *)elem1;
  double *ptr2 = (double *)elem2;
  return *ptr1 == *ptr2;
}

bool equal_str(void *str1, void *str2)
{
  return strcmp((const char *)str1, (const char *)str2) == 0;
}

bool equal_str_ci(void *str1, void *str2)
{
  return compare_str_ci(str1, str2) == 0;
}

bool equal_ptr(void *ptr1, void *ptr2)
{
  return ptr1 == ptr2;
}