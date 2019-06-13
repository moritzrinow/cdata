#include "cdata.h"
#include <string.h>
#include <stdio.h>
#include "test.h"

void print_int_str(key_val_pair_t pair)
{
  int32_t key = *(int32_t *)pair.key;
  char *val = (char *)pair.val;
  printf("%d:%s\n", key, val);
}

bool key_compare_int32(void *n1, void *n2)
{
	int32_t *ptr1 = (int32_t *)n1;
	int32_t *ptr2 = (int32_t *)n2;
	return *ptr1 == *ptr2;
}

int test_rehash()
{
  bool result;
	map_t map;
	map_func_t f;
	f.key_compare = key_compare_int32;
	f.key_destroy = free;
	f.key_hash = hash_int32;
	f.val_destroy = NULL;
  char *str = "A nice little sentence";

  result = map_init(&map, 5, f, true);
	if(!result){
		return 1;
	}

  for(int32_t i = 0; i < 10; i++){
    int32_t *key = (int32_t *)malloc(sizeof(int32_t));
    *key = i;
    void *val = map_add_key_value(&map, key, str);
    if(!val){
      return 1;
    }
  }
  //map_foreach_key_val(&map, print_int_str);
  map_rehash(&map);
  //map_foreach_key_val(&map, print_int_str);
  map_destroy(&map);
  return 0;
}

int test_common()
{
	bool result;
	map_t map;
	map_func_t f;
	f.key_compare = key_compare_int32;
	f.key_destroy = free;
	f.key_hash = hash_int32;
	f.val_destroy = free;

	result = map_init(&map, 1024, f, true);
	if(!result){
		return 1;
	}

	int32_t *key1 = (int32_t *)malloc(sizeof(int32_t));
	int32_t *key2 = (int32_t *)malloc(sizeof(int32_t));
	int32_t *key3 = (int32_t *)malloc(sizeof(int32_t));
	int32_t *key4 = (int32_t *)malloc(sizeof(int32_t));
	int32_t *key5 = (int32_t *)malloc(sizeof(int32_t));
	*key1 = 1;
	*key2 = 2;
	*key3 = 3;
	*key4 = 4;
	*key5 = 5;

	char *val1 = (char *)malloc(1024);
	char *val2 = (char *)malloc(1024);
	char *val3 = (char *)malloc(1024);
	char *val4 = (char *)malloc(1024);
	char *val5 = (char *)malloc(1024);
	strcpy(val1, "A nice one!");
	strcpy(val2, "A nice two!");
	strcpy(val3, "A nice three!");
	strcpy(val4, "A nice four!");
	strcpy(val5, "A nice five!");

	map_add_key_value(&map, key1, val1);
	map_add_key_value(&map, key2, val2);
	map_add_key_value(&map, key3, val3);
	map_add_key_value(&map, key4, val4);
	map_add_key_value(&map, key5, val5);

	char *value;
	value = (char *)map_lookup(&map, key1);
	value = (char *)map_lookup(&map, key2);
	value = (char *)map_lookup(&map, key3);
	value = (char *)map_lookup(&map, key4);
	value = (char *)map_lookup(&map, key5);

	map_iterator_t iterator;
	for(map_iterator_init(&iterator, &map); iterator.current != NULL; map_iterator_next(&iterator)){
		//printf("%d:%s\n", *(int32_t *)iterator.current->key, iterator.current->value);
	}

	map_destroy(&map);
	return 0;
}

int main(int argc, char **argv)
{
	EXEC_TEST("Common", test_common, 0);
  EXEC_TEST("Rehash", test_rehash, 1000000);

  return 0;
}
