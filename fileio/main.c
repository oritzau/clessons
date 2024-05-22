#include <stdio.h>
#include "read_file.h"

int main(void)
{
	print_file_contents("hello.txt");
	puts("-------------");
	print_file_histogram("hello.txt");
}

void print_file_histogram(const char *filepath)
{
	/* Create a table of the printable ASCII characters 
	 * Count the occurrences of each character, then output the result in this format
	 * c: n
	 * where: c = character, n = count
	 */
}

void print_file_contents(const char *filepath)
{
	FILE *fp = fopen(filepath, "r");
	if (!fp)
		return;

	char c;
	while ((c = getc(fp)) != EOF)
		printf("%c", c);
}
