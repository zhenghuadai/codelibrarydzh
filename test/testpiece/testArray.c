/*
 * =====================================================================================
 *
 *       Filename:  testArray.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/01/2010 09:47:23 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

char a[15][128];
int main()
{
	printf("%0x\n", a[1]);
	printf("%0x\n", &a[1]);
}
