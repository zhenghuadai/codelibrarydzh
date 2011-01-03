/*
 * =====================================================================================
 *
 *       Filename:  testCast.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/27/2010 02:13:59 PM
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
void f(unsigned char c);
/**
 * @brief 
 *
 * @param argc
 * @param argv
 *
 * @return 
 */
int main(int argc, char** argv)
{
	unsigned short us = 257;
	us = atoi(argv[1]);
	printf("%d\n", us);
	unsigned char uc= static_cast<unsigned char>(us);
	unsigned char uc2= us;
	f(uc);
}
