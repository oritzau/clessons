#include "cpython.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int test1()
{
	char *array = "Hello!";
	char *separator = ", ";
	char *joined = join(array, separator);
	int passed = !strcmp(joined, "H, e, l, l, o, !");
	free(joined);
	return passed;
}

int test2()
{
	char *string = "Hey, what's good, how,are you, ";
	char *pattern = ", ";

	char *correct[4];
	correct[0] = "Hey";
	correct[1] = "what's good";
	correct[2] = "how,are you";
	correct[3] = "";
	int result_size, sum = 0;
	char **arr = split(string, pattern, &result_size);
	if (!arr) return 0;
	for (int i = 0; i < result_size; i++)
	{
		sum += strcmp(arr[i], correct[i]);
		free(arr[i]);
	}
	free(arr);
	return !sum;
}

int test3()
{
	struct Person people[3];
	people[0] = person_new("Steve", 57);
	people[1] = person_new("Owen", 20);
	people[2] = person_new("Nina", 40);
	struct Person *sorted_people = sorted(people, sizeof(struct Person), 3, &person_cmp);
	int passed = !(strcmp(sorted_people[0].name, "Owen") + strcmp(sorted_people[1].name, "Nina") + strcmp(sorted_people[2].name, "Steve"));
	free(sorted_people);
	return passed;
}

int test4()
{
	int nums[] = {-2, 1, 6, -17, 14};
	int correct[] = {-17, -2, 1, 6, 14};
	int *sorted_nums = sorted(nums, sizeof(int), 5, int_cmp);
	int sum = 0;
	for (int i = 0; i < 5; i++)
	{
		printf("sorted_nums[i]: %d, correct[i]: %d\n", sorted_nums[i], correct[i]);
		sum += sorted_nums[i] == correct[i];
	}
	return sum == 5;
}

int main(void)
{
	if (!test1())
	{
		puts("ERROR: join not correctly implemented!");
		exit(1);
	}
	if (!test2())
	{
		puts("ERROR: split not correctly implemented!");
		exit(1);
	}
	if (!test3())
	{
		puts("ERROR: sorted not correctly implemented!");
		exit(1);
	}
	if (!test4())
	{
		puts("ERROR: sorted not correctly implemented!");
		exit(1);
	}
	puts("All tests passing!!");
}
