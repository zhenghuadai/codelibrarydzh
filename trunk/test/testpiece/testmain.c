/*
 * =====================================================================================
 *
 *       Filename:  testmain.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/27/2010 01:30:08 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <string.h>

void first() __attribute__ ((constructor));

int main() {
	printf("This function is %s ", __FUNCTION__);
	return 0;
}

void first() {
	printf("This %s is before main ", __FUNCTION__);
}
