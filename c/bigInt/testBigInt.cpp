/*
 * =====================================================================================
 *
 *       Filename:  testBigInt.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/12/2008 05:59:35 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhenghua Dai (Zhenghua Dai), djx.zhenghua@gamil.com
 *        Company:  dzh
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#define CONSTTTT 
#include "bigInt.h"
typedef struct {
	bigInt big;
	bigInt* getp(){return &big;}
}bigIntc;

class large
{
	public:
		large(){
			set0_bigInt_(m.getp());
		};

		large(const large& o){
			bigInt_assign_((m.getp()),(o.get().getp()));
		};
		large(int a){}
		bigIntc get()const{return m;}
		bigIntc& get(){return m;}

		bigInt* getp() {return &(m.big);}

		void 	print(){
			printbigInt(&(m.big));
		}
		//large operator=(large& o){return large(o); }
	private:
		bigIntc m;
};

large operator + (const large& s1,const large& s2)
{
	large tmpLarge(s1);
	bigInt_add_(tmpLarge.get().getp(),s2.get().getp());	
	return tmpLarge;
}

//large operator *(Clarge& s1,large &s2)
//{
//large tmpLarge(s1);
//bigInt_mul_(tmpBig,s1,s2);
//return tmpLarge;
//}

void testaddBig()
{
	large a,b,c;
	int i;
	for(i=0;i<64;i++){
	a.getp()[0][i] = 0x0000000000000001;
	b.getp()[0][i] = 0xfffffffffffffffc;
	}
	c = a + b;
	//bigInt_add_(&a,&b);
	c.print();
}

int main()
{
	testaddBig();
}
