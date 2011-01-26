#include "stdlib.h"
/**
 * @brief 
 *
 * @return 
 * b=25
 * a=7
 */
int main()
{
	int a = 5;
	int b;
	b = (a++) *(a++);
	printf("%d\n", b);
	printf("%d\n", a);
}
