#include "cpython.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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
	int *i1 = (int *)a;
	int *i2 = (int *)b;
	return *i1 - *i2;
}

void split_free(char **split, int split_len)
{
	for (int i = 0; i < split_len; i++)
		free(split[i]);
	free(split);
}

char *join(char *array, char *separator)
{
	int array_len, separator_len, joined_len, i, index;
	char *joined;

	array_len = strlen(array);
	separator_len = strlen(separator);
	joined_len = array_len + separator_len * (array_len - 1);
	joined = malloc(sizeof(char) * (joined_len + 1));
	joined[joined_len] = '\0';
	i = 0;
	index = 0;
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

	int string_len, pattern_len;
	int i, j, offset;
	char **result;

	string_len = strlen(string);
	pattern_len = strlen(pattern);
	*result_size = 0;
	result = (char**)malloc(string_len * sizeof(char*));

	for (i = 0; i < string_len; i++)
		result[i] = calloc(MAXSPLITSIZE, sizeof(char));

	i = j = offset = 0;
	while (string[i])
	{
		while (string[i] == pattern[j])
		{
			if (j == pattern_len - 1)
			{
				// We've reached the end of a pattern, copy from offset to current index, minus the pattern
				memcpy(result[*result_size], string+ offset, i - offset - pattern_len + 1);
				offset = i + 1;
				*result_size += 1;
				break;
			}
			j++;
			i++;
		}
		j = 0;
		i++;
	}
	
	// Copy in whatever is left of the string after last pattern, update size
	memcpy(result[*result_size], string + offset, i - pattern_len);
	*result_size += 1;
	
	// Free blocks we didn't use
	for (i = *result_size; i < string_len; i++)
		free(result[i]);
	return result;
}

void debug_person_arr(void *people, int left, int right)
{
	struct Person *peeps = people;
	printf("[BEGIN PERSON ARRAY]\n");
	for (int i = left; i < right; i++)
	{
		printf("Person {name : %s, age: %d}\n", peeps[i].name, peeps[i].age);
	}
	printf("[END PERSON ARRAY]\n");
}

void merge(void *items, int item_size, int left, int mid, int right, cmp_func cmp)
{
	int i, j;
	int k = left * item_size;
	int L_len = item_size * (mid - left);
	int R_len = item_size * (right - mid);
	char *L, *R;

	L = malloc(sizeof(char) * L_len);
	R = malloc(sizeof(char) * R_len);
	// Void Pointer Arithmetic Is Bad
	char *vpaib = (char *)items;
	memcpy(L, vpaib + left * item_size, L_len);
	memcpy(R, vpaib + mid * item_size, R_len);
	i = j = 0;
	
	while (i < L_len && j < R_len)
	{
		int r = cmp(L + i, R + j);
		if (r < 0)
		{
			memcpy(vpaib + k, L + i, item_size);
			i += item_size;
		} else
		{
			memcpy(vpaib + k, R + j, item_size);
			j += item_size;
		}
		k += item_size;
	}

	if (i < L_len)
		memcpy(vpaib + k, L + i, L_len - i);
	if (j < R_len)
		memcpy(vpaib + k, R + j, R_len - j);

	free(L);
	free(R);
}

void *mergesort(void *items, int item_size, int left, int right, cmp_func cmp)
{
	if (left < right)
	{
		int mid = (right + left) / 2;
		if (right - left > 1)
		{
			mergesort(items, item_size, left, mid, cmp);
			mergesort(items, item_size, mid, right, cmp);
		}
		merge(items, item_size, left, mid, right, cmp);
	}

	return items;
}

// Return new copy of items, sorted by comparison cmp
void *sorted(void *items, int num_items, int item_size, cmp_func cmp)
{
	void *items_copy = malloc(item_size * num_items);
	memcpy(items_copy, items, item_size * num_items);
	return mergesort(items_copy, item_size, 0, num_items, cmp);
}

void *insertion_sorted(void *items, int num_items, int item_size, cmp_func cmp)
{
	void *items_copy, *tmp;
	// Void Pointer Arithmetic Is Bad
	char *vpaib;
	items_copy = malloc(item_size * num_items);
	memcpy(items_copy, items, item_size * num_items);
	tmp = malloc(item_size);
	for (int i = item_size; i < item_size * num_items; i += item_size)
	{
		for (int j = i - item_size; j >= 0; j -= item_size)
		{
			vpaib = (char *)items_copy;
			void *curr = vpaib + i;
			void *compare = vpaib + j;
			if (cmp(curr, compare) < 0)
			{
				memcpy(tmp, curr, item_size);
				memcpy(curr, compare, item_size);
				memcpy(compare, tmp , item_size);
				i -= item_size;
			}
		}
	}
	free(tmp);
	return items_copy;
}


