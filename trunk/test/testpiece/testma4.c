/*
 * =====================================================================================
 *
 *       Filename:  testma4.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/18/2010 05:23:07 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#define DEFAULT 40      /* 默认参数值*/
#define FUN(A) fun(#A##"-")    /* 用于实现默认参数的宏*/

int f(int n)  /* 用于实验默认参数的函数*/
{
	return printf("%d\n",n);
}
int fun(const char *a)    /* 确定函数调用的函数,返回值类型要和实际需要调用的f()函数返回值类型一致*/
{
	int n; /* 变量的类型要和f()函数参数的类型一样*/
	if (a[0]=='-') n=DEFAULT;
	else sscanf(a,"%d",&n);

	return f(n);

}
int main(void)
{
	FUN();
	FUN(67);
	return 0;
}

