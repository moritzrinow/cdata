#include "cdata.h"
#include "test.h"

int test_address()
{
  typedef struct person_s {
    int32_t               age;
    float                 weight;
    float                 height;
  }person_t;

  bool result;
  set_t set;
  set_func_t func;
  func.elem_compare = equal_ptr;
  func.elem_destroy = NULL;
  func.elem_hash = hash_uint64;

  result = set_init(&set, 1024, func, true);
  if(!result){
    return 1;
  }

  person_t *people = (person_t *)malloc(sizeof(person_t) * 5);
  for(int i = 0; i < 5; i++){
    people[i].age = i;
    people[i].height = (float)i;
    people[i].weight = (float)i;
  }

  person_t *p1 = &people[0];
  person_t *p2 = &people[1];
  person_t *p3 = &people[2];
  person_t *p4 = &people[3];
  person_t *p5 = &people[4];

  result = set_add_elem(&set, &p1);
  result = set_add_elem(&set, &p2);
  result = set_add_elem(&set, &p3);
  result = set_add_elem(&set, &p4);
  result = set_add_elem(&set, &p5);

  result = set_lookup(&set, &p1);
  result = set_lookup(&set, &p2);
  result = set_lookup(&set, &p3);
  result = set_lookup(&set, &p4);
  result = set_lookup(&set, &p5);

  set_destroy(&set);
  free(people);
}

int test_common()
{
  bool result;
  set_t set;
  set_func_t func;
  func.elem_compare = equal_int32;
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
  EXEC_TEST("Common Hashset Test", test_common, 0);
  EXEC_TEST("Address Test", test_address, 1000000);

  return 0;
}