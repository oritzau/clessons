#include <stdio.h>
#include "../read_file.h"

int main(void)
{
	print_file_contents("../hello.txt");
	puts("-------------");
	print_file_histogram("../hello.txt");
}

void print_file_histogram(const char *filepath)
{
	FILE *fp = fopen(filepath, "r");
	if (!fp)
		return;
	int count[TABLE_SIZE] = { 0 };

	char c;
	while ((c = getc(fp)) != EOF)
	{
		if (c < MIN_PRINTABLE || c > MAX_PRINTABLE)
			continue;
		count[c - MIN_PRINTABLE] += 1;
	}
	for (int i = 0; i < TABLE_SIZE; i++)
		printf("%c: %d\n", i + MIN_PRINTABLE, count[i]);
}

void print_file_contents(const char *filepath)
{
	FILE *fp = fopen(filepath, "r");
	if (!fp)
		return;

	char c;
	while ((c = getc(fp)) != EOF)
	{
		printf("%c", c);
	}
}
