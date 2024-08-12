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
	struct Person people[6];
	people[0] = person_new("Steve", 57);
	people[1] = person_new("Owen", 20);
	people[2] = person_new("Chief Keef", 200);
	people[3] = person_new("Sneed", 13);
	people[4] = person_new("Chuck", 79);
	people[5] = person_new("Nina", 40);
	struct Person *sorted_people = sorted(people, sizeof(struct Person), (sizeof people) / sizeof(struct Person), &person_cmp);
	int passed = !(
		strcmp(sorted_people[0].name, "Sneed") + 
		strcmp(sorted_people[1].name, "Owen") + 
		strcmp(sorted_people[2].name, "Nina") +
		strcmp(sorted_people[3].name, "Steve") +
		strcmp(sorted_people[4].name, "Chuck") +
		strcmp(sorted_people[5].name, "Chief Keef")
	);
	free(sorted_people);
	return passed;
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
