#include "stdlib.h"
int main()
{
	int a = 5;
	int b;
	b = (a++) *(a++);
	printf("%d\n", b);
	printf("%d\n", a);
}
