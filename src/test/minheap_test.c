#include "cdata.h"
#include "test.h"
#include <stdio.h>
#include <time.h>

void print_minheap_int32(minheap_t *heap)
{
  array_iterator_t i;
  for(array_iterator_init(&i, &heap->array); i.current != NULL; array_iterator_next(&i)){
    int32_t *ptr = (int32_t *)i.current;
    printf("%d\n", *ptr);
  }
  printf("\n");
}

int common_test()
{
  int32_t number;
  bool result;
  minheap_t heap;
  minheap_func_t func;
  func.elem_compare = compare_int32;

  result = minheap_init(&heap, func, sizeof(int32_t), 0, true);
  if(!result){
    return 1;
  }

  srand(time(NULL));
  for(int32_t i = 0; i < 1000; i++){
    int32_t r = rand();
    result = minheap_push(&heap, &r);
  }
  for(int32_t i = 0; i < 1000; i++){
    result = minheap_peek(&heap, &number);
    printf("%d\n", number);
    result = minheap_poll(&heap, &number);
  }
  
  minheap_destroy(&heap);
  return 0;
}

int main(int argc, char **argv)
{
  EXEC_TEST("Common test", common_test, 1000000);

  return 0;
}