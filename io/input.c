#include <stdio.h>

int main(void)
{
	int x = 1;
	printf("Input a value for x, or break this by not entering a number: ");
	if (!scanf("%d", &x))
		return 1;
	printf("x: %d\n", x);
}
