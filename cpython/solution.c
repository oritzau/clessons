#include "cpython.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person person_new(char *name, int age) {
  struct Person p;
  p.name = name;
  p.age = age;
  return p;
}

int person_cmp(const void *a, const void *b) {
  struct Person *p1, *p2;
  p1 = (struct Person *)a;
  p2 = (struct Person *)b;
  return p1->age - p2->age;
}

int int_cmp(const void *a, const void *b) {
  int *i1 = (int *)a;
  int *i2 = (int *)b;
  return *i1 - *i2;
}

void split_free(char **split, int split_len) {
  for (int i = 0; i < split_len; i++)
    free(split[i]);
  free(split);
}

char *join(char *array, char *separator);

char **split(char *string, char *pattern, int *result_size);

void merge(void *items, int item_size, int left, int mid, int right,
           cmp_func cmp);

void *mergesort(void *items, int item_size, int left, int right, cmp_func cmp);

void *sorted(void *items, int num_items, int item_size, cmp_func cmp);

void *insertion_sorted(void *items, int num_items, int item_size, cmp_func cmp);
