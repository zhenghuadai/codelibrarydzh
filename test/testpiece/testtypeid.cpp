/*
 * =====================================================================================
 *
 *       Filename:  testtypeid.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/10/2010 04:33:13 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <iostream>
#include <typeinfo>
#define Str2(x) #x
#define Str(x) Str2(x)
using namespace std;
typedef int (*f_t)(int , int);
	template< typename T >
void print_type( T t )
{
	std::cout << typeid(T).name() << std::endl;
}


int main(int argc, char* argv[])
{
	const char *a=0;
	char * b=0;
	int const c=10;
	const int* d=0;
	const int e=0;
	const int &f=e;
	print_type(a);
	print_type(b);
	print_type(c);
	print_type(d);
	print_type(e);
	print_type(f);
	printf("%s\n",  typeid(f_t).name());
    printf("typeof(int): %s\n", Str(typeof(int)));
}
