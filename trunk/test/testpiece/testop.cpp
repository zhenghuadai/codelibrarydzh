/*
 * =====================================================================================
 *
 *       Filename:  testop.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/17/2010 10:54:21 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */


#include	<iostream>
class i{
	int a;
};
int operator+(int s1, i  s2){
std::cout<<"+";
return s1+2;
}

#define atom(x) 
#define atomplusplus(x)\ 
	__asm("lock incl %0":"+m"(x));
//	__asm lock inc dword ptr [x];
// nasm(lock inc, x)
//#define a+ plus
int main()
{
	int a=0,b,c;
	i ai;
	std::cout<<a+b;
	atom(a++);
	atom(a + 2);
	atomplusplus(a);
}
