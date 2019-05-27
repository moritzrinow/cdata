#ifndef _SORT_H
#define _SORT_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "array.h"

void array_sort_bubblesort(array_t *array,
                           array_compare_func_t compare);
void array_sort_bubblesort_std(array_t *array);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _SORT_H
