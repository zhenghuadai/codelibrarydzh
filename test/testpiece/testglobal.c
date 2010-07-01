/*
 * =====================================================================================
 *
 *       Filename:  testglobal.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/18/2010 10:09:30 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h> 
#include <stdlib.h> 
int a[100];

int b;
void f();
int main()
{
//	b= 2;
	f();
	printf("main %d\n",b );
}
