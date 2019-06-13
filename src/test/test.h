#ifndef _TEST_H
#define _TEST_H

#include <stdio.h>

#define EXEC_TEST(name, func, n) \
for(int i = 0; i < n; i++){ \
	int ret = func(); \
	if(ret != 0){ \
		printf("Test '%s' executed with code: %d in cycle %d.\n", name, ret, n); \
	} \
}

#endif // _TEST_H