#include "sort.h"

void array_sort_bubblesort(array_t *array,
                           array_compare_func_t compare)
{
  uint32_t n = array->num_elem;
  uint32_t i;

  do{
    uint32_t newn = 1;
    for(i = 0; i < n - 1; i++){
      void *elem1 = array_get(array, i);
      void *elem2 = array_get(array, i + 1);
      if(compare(elem1, elem2) > 0){
        array_swap(array, i, i + 1);
        newn = i + 1;
      }
    }
    n = newn;
  } while(n > 1);
}

void array_sort_bubblesort_std(array_t *array)
{
  uint32_t n = array->num_elem;
  uint32_t i;

  do{
    uint32_t newn = 1;
    for(i = 0; i < n - 1; i++){
      void *elem1 = array_get(array, i);
      void *elem2 = array_get(array, i + 1);
      if(compare_std(elem1, elem2) > 0){
        array_swap(array, i, i + 1);
        newn = i + 1;
      }
    }
    n = newn;
  } while(n > 1);
}
