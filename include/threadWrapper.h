/*
 * =====================================================================================
 *
 *       Filename:  threadWrapper.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/17/2010 08:26:21 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef  THREADWRAPPER_HEADER__INC
#define  THREADWRAPPER_HEADER__INC

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef float f32;
typedef double f64;
typedef char i8;
typedef short i16;
typedef int i32;
typedef long long i64;
typedef unsigned char *pu8;
typedef unsigned short *pu16;
typedef unsigned int *pu32;
typedef unsigned long long *pu64;
typedef float *pf32;
typedef double *pf64;
typedef char *pi8;
typedef short *pi16;
typedef int *pi32;
typedef long long *pi64;
#ifndef THREAD_NUM
#define THREAD_NUM 2
#endif


#if (!defined(_PTHREAD)) && (!defined(_WINTHREAD))
	#if defined(__GNUC__)
		#define _PTHREAD
	#elif defined(_MSC_VER)
		#define _WINTHREAD 
	#endif
#endif

#ifdef  _PTHREAD
#include <pthread.h>
#include <semaphore.h>
//typedef sem_t           sem_t;
typedef pthread_cond_t    cond_t;
typedef pthread_mutex_t   mutex_t;
typedef pthread_t         thread_t;
typedef pthread_barrier_t barrier_t;

#define declare_sem(x)     sem_t x
#define declare_cond(x)	   pthread_cond_t x= PTHREAD_COND_INITIALIZER
#define declare_mutex(x)   pthread_mutex_t x=PTHREAD_MUTEX_INITIALIZER
#define declare_thread(x)  pthread_t x
#define declare_barrier(x) pthread_barrier_t x

#define create_thread(pfunc, arg) \
{unsigned int tid = tNum; int ret = pthread_create(&tTable[tNum++], NULL, (void *(*)(void *))pfunc, arg);}

#define create_threads(pfunc, arg) {\
	for(;tNum<THREAD_NUM;tNum++){\
		unsigned int tid = tNum;\
		int ret =pthread_create(&tTable[tid], NULL, (void *(*)(void *))pfunc, arg);\
	}\
}

#define create_nthreads(tTable, n, pfunc, arg) {\
	int tid=0;\
    for(tid=0;tid<n;tid++){\
       int ret =pthread_create(&tTable[tid], NULL, (void *(*)(void *))pfunc, arg);\
	}\
}

#define invoke(pfunc) \
{int ret = pthread_create(&tTable[tNum++], NULL, (void *(*)(void *))pfunc, NULL);}

#define close_thread(t) pthread_join(t, NULL);

#define waitall_threads() {\
	int i;\
	for(i=0;i<tNum;i++)\
		close_thread(tTable[i] );\
}

#define THREAD_VAR \
thread_t tTable[THREAD_NUM*2]; \
declare_barrier(tBarrier);\
declare_mutex(tMutex);\
declare_cond(tCond);\
static int tNum=0;\
	
#define INIT_THREAD_VAR()\
pthread_barrier_init(&tBarrier, NULL, THREAD_NUM);

#define FREE_THREAD_VAR() {\
}

#define P(s) pthread_mutex_lock(&s)
#define V(s) pthread_mutex_unlock(&s)

#define mP(s) pthread_mutex_lock(&s)
#define mV(s) pthread_mutex_unlock(&s)

#define sP(s) sem_wait(&s)
#define sV(s) sem_post(&s)
#define sVn(s,n) {int i; for(i=0;i<n,i++)sem_post(&s);}

#define tryP(s) pthread_mutex_trylock(&s); 
#define p() pthread_mutex_lock(&tMutex); 
#define v() pthread_mutex_unlock(&tMutex)
#define condP(cond_s, cond_mutex) pthread_cond_wait(&cond_s, &cond_mutex);
#define condV(cond_s) pthread_cond_signal(&cond_s);
#define Barrier() pthread_barrier_wait(&tBarrier);

#define tfunc_ret void* 
/****************************************************************************************/
/**************************pthread*******************************************************/
/****************************************************************************************/
#else 
/****************************************************************************************/
/**************************win thread****************************************************/
/****************************************************************************************/
#include <windows.h>
#include <process.h>

typedef HANDLE sem_t;
typedef HANDLE cond_t;
typedef HANDLE mutex_t;
typedef HANDLE thread_t;
typedef HANDLE barrier_t;

#define declare_sem(x)     sem_t x=0
#define declare_cond(x)    cond_t x=0
#define declare_mutex(x)   mutex_t x=0
#define declare_thread(x)  thread_t x=0
#define declare_barrier(x) barrier_t x=0

#define create_thread(pfunc, arg) \
        {unsigned int tid = tNum; tTable[tNum++] = (HANDLE)_beginthreadex(NULL, 0, pfunc, arg, 0, NULL);}

#define create_threads(pfunc, arg) {\
	for(;tNum<THREAD_NUM;tNum++){\
		unsigned int threadid;\
		unsigned int tid = tNum;\
        tTable[tNum] = (HANDLE)_beginthreadex(NULL, 0, pfunc, arg, 0, &threadid );\
	}\
}

#define create_nthreads(tTable, n, pfunc, arg) {\
	int tid=0;\
    for(tid=0;tid<n;tid++){\
		unsigned int threadid;\
        tTable[tid] = (HANDLE)_beginthreadex(NULL, 0, pfunc, arg, 0, &threadid );\
	}\
}

#define invoke(pfunc) \
        {tTable[tNum++] = (HANDLE)_beginthreadex(NULL, 0, pfunc, NULL, 0, NULL);}

#define close_thread(t) CloseHandle(t);

#define waitall_threads() {\
	int i=0;\
	WaitForMultipleObjects(tNum, tTable, TRUE, INFINITE);\
	for(i=0;i<tNum;i++){\
		close_thread(tTable[i]);\
	}\
}

#define THREAD_VAR \
thread_t tTable[THREAD_NUM*2]; \
barrier_t tBarrier;\
mutex_t tMutex;\
declare_cond(tCond);\
static int tNum=0;

#define INIT_THREAD_VAR()\
tBarrier= CreateEvent(NULL, TRUE, FALSE, NULL);\
tMutex= /*CreateSemaphore(NULL, 1, 1, NULL); */CreateMutex(NULL,FALSE , 0);

#define FREE_THREAD_VAR() {\
    if(tMutex) CloseHandle(tMutex);\
	if(tBarrier) CloseHandle(tBarrier);\
	if(tCond) CloseHandle(tCond);\
}

#define P(s) WaitForSingleObject(s, INFINITE); 
#define V(s) ReleaseSemaphore(s, 1 ,0)

#define mP(s) WaitForSingleObject(s, INFINITE); 
#define mV(s) ReleaseMutex(s)

#define sP(s) WaitForSingleObject(s, INFINITE); 
#define sV(s) ReleaseSemaphore(s, 1 ,0)
#define sVn(s,n) ReleaseSemaphore(s, n ,0)

#define trymP(s)  

#define p() WaitForSingleObject(tMutex,INFINITE); 
#define v() ReleaseSemaphore(&tMutex, 1, 0)

#define condP(cond_s, cond_mutex) 
#define condV(cond_s) 
#define Barrier()  //WaitForSingleObject(tBarrier, INFINITE);

#define tfunc_ret unsigned WINAPI
//typedef  unsigned WINAPI tfunc_ret ;
#endif   /* ----- #ifndef _PTHREAD  ----- */
/************************************************************************************
 *
 *the Launcher
 *
 ***********************************************************************************/
///////////////// public ////////////////////////////////////////
#define fArgTypename(f) f##Arg_t

#define AAAint(x) int
#define BBBint(x) x 
#define AAApu8(x) pu8
#define BBBpu8(x) x 
#define AAApu32(x) pu32
#define BBBpu32(x) x 


#define AAA(a) AAA##a
#define BBB(a) BBB##a  // BBB(int(a))

//////////////////// 0 args ////////////////////////////////////////////////////
#define structname0()  		struct__ 
#define structname_mid_second0(...) 	structname0(__VA_ARGS__)
#define structname_mid0(...) 			structname_mid_second0(__VA_ARGS__)
#define structname_pre0() 	structname_mid0() 

#define defineArg0()\
	typedef struct{} structname0();

#define defineArgC0()\
	typedef struct{\
	} structname_pre0()

#define defineThreadFunc0(name, arg) \
	typedef structname_pre0 arg name##Arg_t;\
	tfunc_ret name(void*p)

#define poptArg0()

#define pushtArg0()\
}\
}

#define launchfunc0( pfuncKernel) c[tid].func = pfuncKernel; {\
	fArgTypename(pfuncKernel)* pArg = (fArgTypename(pfuncKernel)*)c[tid].kArg;  c[tid].arg= (void*)pArg; pushtArg0 
#define launch0(tid0) { int tid = tid0; launchfunc0  
	
//////////////////// 2 args ////////////////////////////////////////////////////
#define structname2(a00,a01)  		struct__ ## a00 ## a01
#define structname_mid_second2(...) 	structname2(__VA_ARGS__)
#define structname_mid2(...) 			structname_mid_second2(__VA_ARGS__)
#define structname_pre2(a00,a01) 	structname_mid2( AAA(a00),AAA(a01),AAA(a02)) 

#define defineArg2(a00,a01)\
	typedef struct{a00 arg0; a01 arg1;} structname2(a00,a01);

#define defineArgC2(a00,a01)\
	typedef struct{\
		union{AAA(a00) BBB(a00), arg0 ;};\
		union{AAA(a01) BBB(a01), arg1 ;};\
	} structname_pre2(a00,a01)

#define defineThreadFunc2(name, arg) \
	typedef structname_pre2 arg name##Arg_t;\
	tfunc_ret name(void*p)

#define poptArg2(a00,a01)\
	AAA(a00) BBB(a00) = ((structname_pre2(a00,a01)*)p)->arg0 ;\
	AAA(a01) BBB(a01) = ((structname_pre2(a00,a01)*)p)->arg1 ;\

#define pushtArg2(a00,a01)\
	pArg->arg0 =a00; pArg->arg1 =a01; \
}\
}

#define launchfunc2( pfuncKernel) c[tid].func = pfuncKernel; {\
	fArgTypename(pfuncKernel)* pArg = (fArgTypename(pfuncKernel)*)c[tid].kArg;  c[tid].arg= (void*)pArg; pushtArg2 
#define launch2(tid0) { int tid = tid0; launchfunc2  
	
//////////////////// 3 args ////////////////////////////////////////////////////
#define structname3(a00,a01,a02)  		struct__ ## a00 ## a01 ## a02
#define structname_mid_second3(...) 	structname3(__VA_ARGS__)
#define structname_mid3(...) 			structname_mid_second3(__VA_ARGS__)
#define structname_pre3(a00,a01,a02) 	structname_mid3( AAA(a00),AAA(a01),AAA(a02)) 

#define defineArg3(a00,a01,a02)\
	typedef struct{a00 arg0; a01 arg1;	a02 arg2; } structname3(a00,a01,a02);

#define defineArgC3(a00,a01,a02)\
	typedef struct{\
		union{AAA(a00) BBB(a00), arg0 ;};\
		union{AAA(a01) BBB(a01), arg1 ;};\
		union{AAA(a02) BBB(a02), arg2 ;};\
	} structname_pre3(a00,a01,a02)

#define defineThreadFunc3(name, arg) \
	typedef structname_pre3 arg name##Arg_t;\
	tfunc_ret name(void*p)

#define poptArg3(a00,a01,a02)\
	AAA(a00) BBB(a00) = ((structname_pre3(a00,a01,a02)*)p)->arg0 ;\
	AAA(a01) BBB(a01) = ((structname_pre3(a00,a01,a02)*)p)->arg1 ;\
	AAA(a02) BBB(a02) = ((structname_pre3(a00,a01,a02)*)p)->arg2 ;\

#define pushtArg3(a00,a01,a02)\
	pArg->arg0 =a00; pArg->arg1 =a01; pArg->arg2 =a02;\
}\
}

#define launchfunc3( pfuncKernel) c[tid].func = pfuncKernel; {\
	fArgTypename(pfuncKernel)* pArg = (fArgTypename(pfuncKernel)*)c[tid].kArg;  c[tid].arg= (void*)pArg; pushtArg3 
#define launch3(tid0) { int tid = tid0; launchfunc3  
	
//////////////////// 5 args ////////////////////////////////////////////
#define structname5(a, b, c,d,e)  struct__ ## a ## b ## c ## d ## e
#define structname_mid_second5(a, b, c,d,e) structname5(a, b, c,d,e)
#define structname_mid5(a, b, c,d,e) structname_mid_second5(a, b, c,d,e)
#define structname_pre5(a, b, c,d,e) structname_mid5( AAA(a), AAA(b), AAA(c), AAA(d), AAA(e)) 

#define defineArgC5(a, b, c, d, e)\
	typedef struct{\
		union{AAA(a) BBB(a), arg0;};\
		union{AAA(b) BBB(b), arg1;};\
		union{AAA(c) BBB(c), arg2;};\
		union{AAA(d) BBB(d), arg3;};\
		union{AAA(e) BBB(e), arg4;};\
	} structname_pre5(a, b, c, d, e)

#define defineThreadFunc5(name, arg) \
	typedef structname_pre5 arg name##Arg_t;\
	tfunc_ret name(void*p)
//////////////////// 6 args ////////////////////////////////////////////////////

#define structname6(a, b, c,d,e,f)  struct__ ## a ## b ## c ## d ## e ## f
#define structname_mid_second6(a, b, c,d,e,f) structname6(a, b, c,d,e,f)
#define structname_mid6(a, b, c,d,e,f) structname_mid_second6(a, b, c,d,e,f)
#define structname_pre6(a, b, c,d,e,f) structname_mid6( AAA(a), AAA(b), AAA(c), AAA(d), AAA(e), AAA(f)) 

#define defineArgC6(a, b, c, d, e,f)\
	typedef struct{\
		union{AAA(a) BBB(a), arg0;};\
		union{AAA(b) BBB(b), arg1;};\
		union{AAA(c) BBB(c), arg2;};\
		union{AAA(d) BBB(d), arg3;};\
		union{AAA(e) BBB(e), arg4;};\
		union{AAA(e) BBB(f), arg5;};\
	} structname_pre6(a, b, c, d, e,f)

#define defineThreadFunc6(name, arg) \
	typedef structname_pre6 arg name##Arg_t;\
	tfunc_ret name(void*p)


#define poptArg6( a, b,c,d,e,f)\
	AAA(a) BBB(a) = ((structname_pre6(a,b,c,d,e,f)*)p)->arg0;\
	AAA(b) BBB(b) = ((structname_pre6(a,b,c,d,e,f)*)p)->arg1;\
	AAA(c) BBB(c) = ((structname_pre6(a,b,c,d,e,f)*)p)->arg2;\
	AAA(c) BBB(d) = ((structname_pre6(a,b,c,d,e,f)*)p)->arg3;\
	AAA(c) BBB(e) = ((structname_pre6(a,b,c,d,e,f)*)p)->arg4;\
	AAA(c) BBB(f) = ((structname_pre6(a,b,c,d,e,f)*)p)->arg5 

#define pushtArg6(a, b, c,d,e,f)\
	pArg->arg0=a;\
	pArg->arg1=b;\
	pArg->arg2=c;\
	pArg->arg3=d;\
	pArg->arg4=e;\
	pArg->arg5=f;\
}\
}

#define launchfunc6( pfuncKernel) c[tid].func = pfuncKernel; {\
	fArgTypename(pfuncKernel)* pArg = (fArgTypename(pfuncKernel)*)c[tid].kArg;  c[tid].arg= (void*)pArg; pushtArg6 
#define launch6(tid0) { int tid = tid0; launchfunc6  

//////////////////// 16 args ////////////////////////////////////////////////////
#define structname16(a00,a01,a02,a03,a04,a05,a06,a07,a08,a09,a10,a11,a12,a13,a14,a15)  \
	struct__ ## a00 ## a01 ## a02 ## a03 ## a04 ## a05 ## a06 ## a07 ## a08 ## a09 ## a10 ## a11 ## a12 ## a13 ## a14 ## a15
#define structname_mid_second16(...) structname16(__VA_ARGS__)
#define structname_mid16(...) structname_mid_second16(__VA_ARGS__)
#define structname_pre16(a00,a01,a02,a03,a04,a05,a06,a07,a08,a09,a10,a11,a12,a13,a14,a15) \
	structname_mid6( AAA(a00),AAA(a01),AAA(a02),AAA(a03),AAA(a04),AAA(a05),AAA(a06),AAA(a07),AAA(a08),AAA(a09),AAA(a10),AAA(a11),AAA(a12),AAA(a13),AAA(a14),AAA(a15)) 

#define defineArgC16(a00,a01,a02,a03,a04,a05,a06,a07,a08,a09,a10,a11,a12,a13,a14,a15)\
	typedef struct{\
		union{AAA(a00) BBB(a00), arg0 ;};\
		union{AAA(a01) BBB(a01), arg1 ;};\
		union{AAA(a02) BBB(a02), arg2 ;};\
		union{AAA(a03) BBB(a03), arg3 ;};\
		union{AAA(a04) BBB(a04), arg4 ;};\
		union{AAA(a05) BBB(a05), arg5 ;};\
		union{AAA(a06) BBB(a06), arg6 ;};\
		union{AAA(a07) BBB(a07), arg7 ;};\
		union{AAA(a08) BBB(a08), arg8 ;};\
		union{AAA(a09) BBB(a09), arg9 ;};\
		union{AAA(a10) BBB(a10), arg10;};\
		union{AAA(a10) BBB(a10), arg10;};\
		union{AAA(a12) BBB(a12), arg12;};\
		union{AAA(a13) BBB(a13), arg13;};\
		union{AAA(a14) BBB(a14), arg14;};\
		union{AAA(a15) BBB(a15), arg15;};\
	} structname_pre16(a00,a01,a02,a03,a04,a05,a06,a07,a08,a09,a10,a11,a12,a13,a14,a15)

#define defineThreadFunc16(name, arg) \
	typedef structname_pre16 arg name##Arg_t;\
	tfunc_ret name(void*p)

#define poptArg16(a00,a01,a02,a03,a04,a05,a06,a07,a08,a09,a10,a11,a12,a13,a14,a15)\
	AAA(a00) BBB(a00) = ((structname_pre16(a00,a01,a02,a03,a04,a05,a06,a07,a08,a09,a10,a11,a12,a13,a14,a15)*)p)->arg0 ;\
	AAA(a01) BBB(a01) = ((structname_pre16(a00,a01,a02,a03,a04,a05,a06,a07,a08,a09,a10,a11,a12,a13,a14,a15)*)p)->arg1 ;\
	AAA(a02) BBB(a02) = ((structname_pre16(a00,a01,a02,a03,a04,a05,a06,a07,a08,a09,a10,a11,a12,a13,a14,a15)*)p)->arg2 ;\
	AAA(a03) BBB(a03) = ((structname_pre16(a00,a01,a02,a03,a04,a05,a06,a07,a08,a09,a10,a11,a12,a13,a14,a15)*)p)->arg3 ;\
	AAA(a04) BBB(a04) = ((structname_pre16(a00,a01,a02,a03,a04,a05,a06,a07,a08,a09,a10,a11,a12,a13,a14,a15)*)p)->arg4 ;\
	AAA(a05) BBB(a05) = ((structname_pre16(a00,a01,a02,a03,a04,a05,a06,a07,a08,a09,a10,a11,a12,a13,a14,a15)*)p)->arg5 ;\
	AAA(a06) BBB(a06) = ((structname_pre16(a00,a01,a02,a03,a04,a05,a06,a07,a08,a09,a10,a11,a12,a13,a14,a15)*)p)->arg6 ;\
	AAA(a07) BBB(a07) = ((structname_pre16(a00,a01,a02,a03,a04,a05,a06,a07,a08,a09,a10,a11,a12,a13,a14,a15)*)p)->arg7 ;\
	AAA(a08) BBB(a08) = ((structname_pre16(a00,a01,a02,a03,a04,a05,a06,a07,a08,a09,a10,a11,a12,a13,a14,a15)*)p)->arg8 ;\
	AAA(a09) BBB(a09) = ((structname_pre16(a00,a01,a02,a03,a04,a05,a06,a07,a08,a09,a10,a11,a12,a13,a14,a15)*)p)->arg9 ;\
	AAA(a10) BBB(a10) = ((structname_pre16(a00,a01,a02,a03,a04,a05,a06,a07,a08,a09,a10,a11,a12,a13,a14,a15)*)p)->arg10;\
	AAA(a10) BBB(a10) = ((structname_pre16(a00,a01,a02,a03,a04,a05,a06,a07,a08,a09,a10,a11,a12,a13,a14,a15)*)p)->arg10;\
	AAA(a12) BBB(a12) = ((structname_pre16(a00,a01,a02,a03,a04,a05,a06,a07,a08,a09,a10,a11,a12,a13,a14,a15)*)p)->arg12;\
	AAA(a13) BBB(a13) = ((structname_pre16(a00,a01,a02,a03,a04,a05,a06,a07,a08,a09,a10,a11,a12,a13,a14,a15)*)p)->arg13;\
	AAA(a14) BBB(a14) = ((structname_pre16(a00,a01,a02,a03,a04,a05,a06,a07,a08,a09,a10,a11,a12,a13,a14,a15)*)p)->arg14;\
	AAA(a15) BBB(a15) = ((structname_pre16(a00,a01,a02,a03,a04,a05,a06,a07,a08,a09,a10,a11,a12,a13,a14,a15)*)p)->arg15;\

#define pushtArg16(a00,a01,a02,a03,a04,a05,a06,a07,a08,a09,a10,a11,a12,a13,a14,a15)\
	pArg->arg0 =a00;\
	pArg->arg1 =a01;\
	pArg->arg2 =a02;\
	pArg->arg3 =a03;\
	pArg->arg4 =a04;\
	pArg->arg5 =a05;\
	pArg->arg6 =a06;\
	pArg->arg7 =a07;\
	pArg->arg8 =a08;\
	pArg->arg9 =a09;\
	pArg->arg10=a10;\
	pArg->arg10=a10;\
	pArg->arg12=a12;\
	pArg->arg13=a13;\
	pArg->arg14=a14;\
	pArg->arg15=a15;\
}\
}

#define launchfunc16( pfuncKernel) c[tid].func = pfuncKernel; {\
	fArgTypename(pfuncKernel)* pArg = (fArgTypename(pfuncKernel)*)c[tid].kArg;  c[tid].arg= (void*)pArg; pushtArg16 
#define launch16(tid0) { int tid = tid0; launchfunc16  
	
/************************************************************************************
 *
 *the Launcher end
 *
 ***********************************************************************************/

#endif   /* ----- #ifndef THREADWRAPPER_HEADER__INC  ----- */
