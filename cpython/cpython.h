/*
* Implement the following Python standard library functions in C, using the headings provided below
*	str.join(array):
*		Join the element of an iterable into a string
*
*	str.split(pattern):
*		Split a string into an array of strings based on a pattern
*
* And for extra credit,
*	sorted(array, key)
*		Returns an array of items sorted by comparitor function key
*/

typedef int(*cmp_func)(const void *a, const void *b);

char *join(char *array, char *separator);
char **split(char *string, char *pattern, int *result_size);
void *sorted(void *items, int item_size, int num_items, cmp_func cmp);
void *insertion_sorted(void *items, int item_size, int num_items, cmp_func cmp);

// The following is helper code for the tests that should pass when functions are implemented correctly
struct Person
{
	char *name;
	int age;
};

// Maximum length a char * in the split array can be
#define MAXSPLITSIZE 256

struct Person person_new(char *name, int age);
int person_cmp(const void *a, const void *b);

int int_cmp(const void *a, const void *b);

// helper for freeing space allocated by split
void split_free(char **split, int split_len);
