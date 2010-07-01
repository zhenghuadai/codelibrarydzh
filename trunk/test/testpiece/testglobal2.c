/*
 * =====================================================================================
 *
 *       Filename:  testglobal2.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/18/2010 10:10:20 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>
int a[100];
int b=10000;

void f(){
//	b = 20000;
	printf("%d\n", sizeof(a));
	printf("f %d\n",b );
}
