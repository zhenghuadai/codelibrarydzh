/*
 * =====================================================================================
 *
 *       Filename:  test2.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/13/2010 10:44:55 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <iostream>
using namespace std;
class A
{};

class B
{
	void f(){}
	int i;
};

class C
{
	virtual void f(){}
};

class D:public B,public C
{};

int main(){

int n1 = sizeof(A);
int n2 = sizeof(B);
int n3 = sizeof(C);
int n4 = sizeof(D);
cout<<n1<<endl;
cout<<n2<<endl;
cout<<n3<<endl;
cout<<n4<<endl;
}
