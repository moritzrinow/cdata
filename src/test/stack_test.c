#include "cdata.h"
#include "test.h"

int common_test()
{
  int32_t elem;
  bool result;
  stack_t stack;
  result = stack_init(&stack, sizeof(int32_t), 1024, true);
  if(!result){
    return 1;
  }

  STACK_PUSH(&stack, int32_t, 1);
  STACK_PUSH(&stack, int32_t, 2);
  STACK_PUSH(&stack, int32_t, 3);
  STACK_PUSH(&stack, int32_t, 4);
  STACK_PUSH(&stack, int32_t, 5);

  result = stack_pop(&stack, &elem);
  //printf("%d\n", elem);

  result = stack_pop(&stack, &elem);
  //printf("%d\n", elem);

  result = stack_pop(&stack, &elem);
  //printf("%d\n", elem);

  result = stack_pop(&stack, &elem);
  //printf("%d\n", elem);

  result = stack_pop(&stack, &elem);
  //printf("%d\n", elem);

  stack_destroy(&stack);
  return 0;
}

int main(int argc, char **argv)
{
  EXEC_TEST("Common test", common_test, 10000000);
  return 0;
}
