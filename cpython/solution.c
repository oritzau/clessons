#include "cpython.h"
#include <string.h>
#include <stdlib.h>

struct Person person_new(char *name, int age)
{
	struct Person p;
	p.name = name;
	p.age = age;
	return p;
}

int person_cmp(const void *a, const void *b)
{
	struct Person *p1, *p2;
	p1 = (struct Person *)a;
	p2 = (struct Person *)b;
	return p1->age - p2->age;
}

int int_cmp(const void *a, const void *b)
{
	int *x1, *x2;
	x1 = (int *)a;
	x2 = (int*)b;
	return (*x1) - (*x2);
}

char *join(char *array, char *separator)
{
	int array_len = strlen(array);
	int separator_len = strlen(separator);
	int joined_len = array_len + separator_len * (array_len - 1);
	char *joined = malloc(sizeof(char) * (joined_len + 1));
	joined[joined_len] = '\0';
	int i = 0;
	int index = 0;
	while (1)
	{
		joined[i] = array[index];
		if (index == array_len - 1) break;
		for (int j = 0; j < separator_len; j++)
		{
			i++;
			joined[i] = separator[j];
		}
		i++;
		index++;
	}
	return joined;
}

char **split(char *string, char *pattern, int *result_size)
{

	int string_len, pattern_len, i, pattern_index, counter;
	char tmp, *string_cpy, **result;

	string_len = strlen(string);
	pattern_len = strlen(pattern);
	pattern_index = *result_size = i = counter = 0;

	result = (char**)malloc((string_len + 2) * sizeof(char*));
	string_cpy = calloc(string_len + 1, sizeof(char));
	char *string_cpy_orig_location = string_cpy;
	strcpy(string_cpy, string);

	for (i = 0; i < string_len + 2; i++)
		result[i] = calloc(MAXSPLITSIZE, sizeof(char));
	i = 0;

	while (counter < string_len)
	{
		while (string_cpy[i] == pattern[pattern_index]) 
		{
			if (pattern_index == pattern_len - 1)
			{
				// We've matched the pattern, ending at index i
				string_cpy[i - (pattern_len - 1)] = '\0';
				strncpy(result[*result_size], string_cpy, MAXSPLITSIZE);
				string_cpy += i + 1;
				(*result_size)++;
				i = -1;
				pattern_index = 0;
				break;
			}
			i++;
			pattern_index++;
		}
		pattern_index = 0;
		i++;
		counter++;
	}
	strncpy(result[*result_size], string_cpy, MAXSPLITSIZE);
	(*result_size)++;
	free(string_cpy_orig_location);
	return result;
}

void *sorted(void *items, int item_size, int num_items, int (*cmp_func)(const void *, const void *))
{
	void *items_copy = malloc(item_size * num_items);
	memcpy(items_copy, items, item_size * num_items);
	void *tmp = malloc(item_size);
	// qsort(items, num_items, item_size, cmp_func);
	for (int i = item_size; i < item_size * num_items ; i += item_size)
	{
		void *curr = items_copy + i;
		for (int j = i - item_size; j >= 0; j -= item_size)
		{
			void *compare = items_copy + j;
			if (cmp_func(curr, compare) < 0)
			// curr < compare
			{
				memcpy(tmp, curr, item_size);
				memcpy(curr, compare, item_size);
				memcpy(compare, tmp , item_size);
			}
		}
	}
	free(tmp);
	return items_copy;
}


