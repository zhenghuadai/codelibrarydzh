/*
 * =====================================================================================
 *
 *       Filename:  bigInt.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/03/2008 07:36:37 PM
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
#define MAXNUM 64
#define _STR(s) #s
#define STR(s) _STR(s)
typedef unsigned long long U64; 
typedef unsigned int U32; 
typedef U64 bigInt[64];
typedef U64 U128[2];
/**********************************************************
 *U64 operation
 * ********************************************************/
//high:low = s1 * s2;
void  u64_mul_(U64& s1,U64& s2,U64& high, U64& low)
{
	__asm(
			"movq %2,%%rax;"\
			"movq %3,%%rdx;"\
			"mulq %%rdx;"\	
			"movq %%rdx, %0;"\
			"movq %%rax,%1;"\
			:"=r"(high),"=r"(low)\
			:"r"(s1),"r"(s2)
			:"%rax","%rdx"
		 );
}

//dst = s1 + s2;
//ret = 1?0:CF:!CF;
inline int  u64_addi_(U64& dst,U64& s1,U64& s2)
{
	int ret=0;
	__asm( 
			"xor %%ecx,%%ecx;"
			"addq %%rax,%%rdx;"
			"adc $0,%%ecx;"
			:"=d"(dst),"=c"(ret)
			:"d"(s1),"a"(s2)
		 );
			return ret;
}

//dst = s1 + s2 + CF;
//ret = 1?0:CF:!CF;
inline int  u64_addci_(U64& dst,U64& s1,U64& s2)
{
	int ret=0;
	__asm( 
			"xor %%ecx,%%ecx;"\
			"adc %%rax,%%rdx;"\
			"adc $0,%%ecx;"\
			:"=d"(dst),"=c"(ret)\
			:"d"(s1),"a"(s2)
		 );
			return 0;
}

//dst = s1 + s2;
inline int  u64_add_(U64& dst,U64& s1,U64& s2)
{
	int ret;
	__asm( 
			"addq %2,%%rdx;"\
			:"=d"(dst)\
			:"0"(s1),"r"(s2)
		 );
			return 0;
}

//dst = s1 + s2 + CF;
inline int  u64_addc_(U64& dst,U64& s1,U64& s2)
{
	int ret;
	__asm( 
			"stc;"\
			"adc %2,%%rdx;"\
			:"=d"(dst)\
			:"0"(s1),"r"(s2)
		 );
			return 0;
}


/**********************************************************
 *bigInt  operation
 * ********************************************************/
#define LOOP2(X)\
X \
X 

#define LOOP4(X)\
X \
X \
X \
X 

#define LOOP8(X) \
LOOP4(X) \
LOOP4(X)

#define LOOP16(X) \
LOOP8(X) \
LOOP8(X) 

#define LOOP32(X) \
LOOP16(X) \
LOOP16(X)

#define LOOP64(X) \
LOOP32(X) \
LOOP32(X)

void  u128_add_(U128& dst,U128 &src,U64& acc)
{
	__asm(
			"clc;"
			"movq (%%rsi),%%rax;" 
			"adc %%rax,(%%rdi);"
			"movq 8(%%rsi),%%rax;" 
			"adc %%rax,8(%%rdi);"
			"adc $0, (%%rbx);"
			:
			:"S"(&src),"D"(&dst),"b"(&acc)
			:"%eax"
		 );

}

inline void  u128_add2_(U64& dst,U64 &src,U64& acc)
{
	u128_add_((U128&)dst,(U128&)src,acc);	
}

//dst += src1
void bigInt_add_(bigInt& dst, bigInt& src1)
{
#define MACROADDONCE1 \
	"movq (%%rsi), %%rax;"\
	"adc %%rax, (%%rdi);"\
	"addq $8, %%rsi;"\
	"addq $8, %%rdi;"


#define MACROADDONCE2bk(offst) \
	movq offst(%%rsi),%%rax; \
	adc %%rax,offst(%%rdi);

#define MACROADDONCE(offst) \
	"movq " STR(offst) "(%%rsi),%%rax;" \
	"adc  %%rax," STR(offst) "(%%rdi);"
#define MACROADDTWO(offst) \
	MACROADDONCE((offst))\
	MACROADDONCE((offst+8))

#define MACROADDFOUR(offst) \
	MACROADDTWO((offst))\
	MACROADDTWO((offst+16))

#define MACROADDEIGHT(offst) \
	MACROADDFOUR((offst))\
	MACROADDFOUR((offst+32))

#define MACROADDSIXTEEN(offst) \
	MACROADDEIGHT((offst))\
	MACROADDEIGHT((offst+64))

#define MACROADD32TEEN(offst) \
	MACROADDSIXTEEN((offst))\
	MACROADDSIXTEEN((offst+128))

#define MACROADD64TEEN(offst) \
	MACROADD32TEEN((offst))\
	MACROADD32TEEN((offst+256))

#define MACROADDALL_(n) MACROADD##n##TEEN(0)
#define MACROADDALL(n) MACROADDALL_(n) 

	__asm(
			"clc;"
			MACROADDALL(MAXNUM)
			:
			:"S"(&src1),"D"(&dst)
			:"%eax"
		 );
}

void bigInt_assign_(bigInt& dst,bigInt& src)
{
	for(int i=0;i< MAXNUM;i++){
		dst[i] = src[i];	
	}
}

void bigInt_complement_(bigInt& dst, bigInt& src)
{
	int i=0;
	//if((dst[MAXNUM-1] && (1L<<31)) ==0) {
	//bigInt_assign_(dst,src);
	//return ;
	//}
	while(src[i] == 0){ dst[i] = src[i];i++;}
	if(i == MAXNUM) return ;
	dst[i] = (~src[i]) + 1;
	while(i<MAXNUM) dst[i] = ~src[i];
}
void set(bigInt& s)
{
	for(int i=0;i< MAXNUM;i++){
		s[i] =0; 
	}
	
}

void bitInt_mul(bigInt& dst,bigInt& src1, bigInt& src2)
{
	set(dst);
	U128 tmp128;
	bigInt tmpAcc;
	set(tmpAcc);
	int idx = 0;
	for(int j=0;j<MAXNUM;j++){
		U64 s0 = src1[j];
		idx = j;
		for(int i=0;i<MAXNUM;i++){
			U64 s1 = src2[i];
			u64_mul_(s0,s1,tmp128[1],tmp128[0]);
			u128_add2_(dst[idx],tmp128[0],tmpAcc[idx+1]);
			idx++;
		}
	}
	bigInt_add_(dst,tmpAcc);
}


U64 mul64(U32& s1,U32& s2)
{
	return s1 * s2;
}
void print16(U64& s)
{
	unsigned int *p =(unsigned int*) &s;
	printf("%16x%16x",*(p+1),*p);
}
void testmul()
{
	int a;
	U64 b,c=0xaaaaaaaaaaaaaaaa,d=0x1111111111111111;
	//U64 b,c=0x0000000000000004,d=0xffffffffffffffff,e=0x8000000000000002;
	U64 high=0,low=0;
	u64_mul_(c,d,high,low);
	print16(high);
	printf("\n");
	print16(low);
	printf("\n");
}
void testadd()
{

	int a;
	U64 b,c=0xaaaaaaaaaaaaaaaa,d=0x1111111111111111;
	//U64 b,c=0x0000000000000004,d=0xffffffffffffffff,e=0x8000000000000002;
	a = u64_add_(b,c,d);
	print16(b);
}
void testadc()
{

	int a;
	U64 b,c=0xaaaaaaaaaaaaaaaa,d=0x1111111111111111;
	//U64 b,c=0x0000000000000004,d=0xffffffffffffffff,e=0x8000000000000002;
	a = u64_addc_(b,c,d);
	print16(b);
}
void testaddi()
{
	int a;
	U64 b,c=0xaaaaaaaaaaaaaaaa,d=0xffffffffffffffff;
	//U64 b,c=0x0000000000000004,d=0xffffffffffffffff,e=0x8000000000000002;
	a = u64_addi_(b,c,d);
	print16(b);
	printf("\n");
	printf("%d\n",a);
}



void printbigInt(bigInt& a)
{

	for(int i=0;i<64;i++){
		print16(a[i]);
	}
}

void testaddBig()
{
	bigInt a,b;
	for(int i=0;i<64;i++){
		a[i] = 0x0000000000000001;
		b[i] = 0xffffffffffffffff;
	}
	bigInt_add_(a,b);
	printbigInt(a);
}

int main(int argc,char** argv)
{
	//testaddi();
	testaddBig();
	printf("\n");
}

/*
   class bigInt {
   private:
   unsigned long long d[MAXNUM];
   public:
   friend bigInt& operator +(bigInt &);
//bigInt& operator =(bigInt &);
void set(unsigned long long a2,unsigned long long a1){
}
};

bigInt& bigInt::operator+(bigInt& s2)
{

}
*/

//bigInt& add(bigInt& s1, bigInt& s2)
//{

//}
