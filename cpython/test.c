#include "cpython.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int test1()
{
	char *array = "Hello!";
	char *separator = ", ";
	char *joined = join(array, separator);
	return !strcmp(joined, "H, e, l, l, o, !");
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
		// printf("[DEBUG] result: \"%s\", correct: \"%s\"\n", arr[i], correct[i]);
		sum += strcmp(arr[i], correct[i]);
	}
	return !sum;
}

int test3()
{
	struct Person people[3];
	people[0] = person_new("Steve", 57);
	people[1] = person_new("Owen", 20);
	people[2] = person_new("Nina", 40);
	struct Person *sorted_people = sorted(people, sizeof(struct Person), 3, &person_cmp);
	free(sorted_people);
	return !(strcmp(people[0].name, "Owen") + strcmp(people[1].name, "Nina") + strcmp(people[2].name, "Steve"));
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
	puts("All tests passing!!");
}
