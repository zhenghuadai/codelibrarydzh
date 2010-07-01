/*
 * =====================================================================================
 *
 *       Filename:  testunion.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/01/2010 04:50:56 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

union a{
	int a, b;
};

int main()
{
	printf("%d\n", sizeof(union a));
}
