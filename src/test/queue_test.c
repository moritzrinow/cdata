#include "cdata.h"
#include "test.h"

int common_test()
{
  int32_t *elem;
  bool result;
  queue_t q;

  result = queue_init(&q, sizeof(int32_t), 1024, true);
  if(!result){
    return 1;
  }

  QUEUE_ENQUEUE(&q, int32_t, 4);
  QUEUE_ENQUEUE(&q, int32_t, 6);
  QUEUE_ENQUEUE(&q, int32_t, 3);
  QUEUE_ENQUEUE(&q, int32_t, 677);
  QUEUE_ENQUEUE(&q, int32_t, 44);

  elem = (int32_t *)queue_dequeue(&q);
  elem = (int32_t *)queue_dequeue(&q);
  elem = (int32_t *)queue_dequeue(&q);
  elem = (int32_t *)queue_dequeue(&q);
  elem = (int32_t *)queue_dequeue(&q);

  queue_destroy(&q);

  return 0;
}

int main(int argc, char **argv)
{
  EXEC_TEST("Common test", common_test, 10000000);

  return 0;
}