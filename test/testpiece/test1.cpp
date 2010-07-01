/*
 * =====================================================================================
 *
 *       Filename:  test1.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/13/2010 10:42:54 AM
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
{
	public:
		~A(){cout<<"~A"<<endl;}
};

class B:public A
{
	public:
		~B(){cout<<"~B"<<endl;}
};

int main(){
A* p = new B;
delete p;
}
