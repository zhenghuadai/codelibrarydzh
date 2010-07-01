#include <stdio.h>

int test(int *p)
{
	int a[100];
	int b;
	__asm__ volatile ( 
		"movl %0 ,%%eax \n"
		"movl %1, %%ebx\n"
		:
		:"r"(b),"r"(*p)
);	
}
