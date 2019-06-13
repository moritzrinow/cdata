#include "cdata.h"
#include "test.h"

bool compare_int32(void *n1, void *n2)
{
  int32_t *ptr1 = (int32_t *)n1;
  int32_t *ptr2 = (int32_t *)n2;
  return *ptr1 == *ptr2;
}

int test_common()
{
  bool result;
  set_t set;
  set_func_t func;
  func.elem_compare = compare_int32;
  func.elem_destroy = NULL;
  func.elem_hash = hash_int32;

  result = set_init(&set, 1024, func, true);
  if(!result){
    return 1;
  }

  int32_t a = -451323;
  int32_t b = 2435345;
  int32_t c = 3431223;
  int32_t d = 2456456;
  int32_t e = 1435435;

  result = set_add_elem(&set, &a);
  result = set_add_elem(&set, &b);
  result = set_add_elem(&set, &c);
  result = set_add_elem(&set, &d);
  result = set_add_elem(&set, &e);

  result = set_lookup(&set, &a);
  result = set_lookup(&set, &b);
  result = set_lookup(&set, &c);
  result = set_lookup(&set, &d);
  result = set_lookup(&set, &e);

  int32_t f = 5023423;
  result = set_lookup(&set, &f);

  set_remove(&set, &a);
  set_remove(&set, &b);
  set_remove(&set, &c);
  set_remove(&set, &d);
  set_remove(&set, &e);

  result = set_lookup(&set, &a);
  result = set_lookup(&set, &b);
  result = set_lookup(&set, &c);
  result = set_lookup(&set, &d);
  result = set_lookup(&set, &e);

  set_destroy(&set);
  return 0;
}

int main(int argc, char **argv)
{
  EXEC_TEST("Common Hashset Test", test_common, 1000000);

  return 0;
}