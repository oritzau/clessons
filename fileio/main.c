#include <stdio.h>
#include "read_file.h"

int main(void)
{
	print_file_contents("hello.txt");

	puts("-------------");
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
