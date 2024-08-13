#include "cpython.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

typedef void *(*sorting_algorithm)(void *items, int num_items, int item_size, cmp_func cmp);

void record_runtime(sorting_algorithm sort, int max_len)
{
	srand(time(0));
	struct timeval t1, t2;

	int *nums = malloc(sizeof(int) * max_len);
	for (int i = 0; i < max_len; i++)
		nums[i] = rand();

	gettimeofday(&t1, 0);
	void *s = sort(nums, max_len, sizeof(int), &int_cmp);
	gettimeofday(&t2, 0);
	free(s);
	printf("Time in seconds to sort %d items: %lu\n", max_len, t2.tv_sec - t1.tv_sec);
}

int main(void)
{
	record_runtime(&sorted, 2e7);
	record_runtime(&insertion_sorted, 27e2);
}
