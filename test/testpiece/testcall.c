/*
 * =====================================================================================
 *
 *       Filename:  testcall.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/06/2010 08:09:50 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#if 0
#ifdef __cplusplus
extern "C" {
#endif   // __cplusplus

	int defaultCall(int param);
	int __cdecl cdeclCall(int param);
	int __stdcall stdCall(int param);
	int __attribute__((stdcall)) attrStdCall(int param);

#ifdef __cplusplus
}
#endif   //__cplusplus

#endif

int  testDefaultf(int a , int b, int c, int d ){
	printf("%d %d %d %d \n", a, b, c, d );
	return 1;
}

int __attribute__((stdcall)) testStdcallf(int a, int b, int c, int d ){
	printf("%d %d %d %d \n", a, b, c, d );
	return 1;
}

int __attribute__((cdecl)) testCdecl(int a , int b, int c, int d ){
	printf("%d %d %d %d \n", a, b, c, d );
	return 1;
}

typedef int (*f_t)(int);
void testf( void* f){
	f_t func = (f_t)f;
	int a ;
	func(a);
	__asm__("call *%%eax"::"a"(f));
}

typedef struct{
	void* f;
	int argSize;
	char esp[128];
}funcInfo_t;

funcInfo_t global_funcInfo;

void* thread_func_g(void*p){
	funcInfo_t* ft = (funcInfo_t*)p;
	__asm__(
	"subl %%ecx, %%esp\n"
	"movl %%esp, %%edi\n"
	"rep movsb\n"
	"call *%%eax\n"
	:
	:"a"(ft->f),"c"(ft->argSize), "S"(ft->esp)
	:"edi");
}

void testcc(int a, char b, short c){

}

int main()
{
	int a = 1;
	int b =2, c=3,d=4;
	char cc=0;
	short sc = 0;
	__typeof__((int*)sc) pint = (int*)0; 

	a = testStdcallf(a, b, c,d);
	a = testCdecl(a, b, c,d);
	a =(__typeof__(a)) testDefaultf(a, b, c,d);
	global_funcInfo.f = (void*) testStdcallf;
	global_funcInfo.argSize = 16;
	global_funcInfo.esp[0]=1;
	global_funcInfo.esp[4]=2;
	global_funcInfo.esp[8]=3;
	global_funcInfo.esp[12]=4;
	thread_func_g(&global_funcInfo);

	testcc(a, cc, sc);
	return a;
}
