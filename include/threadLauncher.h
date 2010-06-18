
#ifndef  THREADLAUNCHER_HEADER__INC
#define  THREADLAUNCHER_HEADER__INC

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
#define structname_mid_second3(a00,a01,a02) 	structname3(a00,a01,a02)
#define structname_mid3(a00,a01,a02) 			structname_mid_second3(a00,a01,a02)
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
	AAA(a02) BBB(a02) = ((structname_pre3(a00,a01,a02)*)p)->arg2 \

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
////////////////////////***** launch a single function **////////////////////////////
typedef struct{
	void* f;
	int argSize;
	char esp[128];
}funcInfo_t;
static funcInfo_t global_funcInfo;

#ifdef _PTHREAD
#define push2stack(v) (*(typeof(v)*)pcur)=v 

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  thread_func_g
 *  Description:  the thread template for launching simple function,
 *                it copy the arguments from p->esp to the stack, then call the p->f;
 *  	  Input:  
 *       Output:
 *      Example:  thread_func_g
 * =====================================================================================
 */
static void* thread_func_g(void*p){
	funcInfo_t* ft = (funcInfo_t*)p;
    printf("%0x - %0x = %d\n", (unsigned int) pthread_self(), &ft, (unsigned int) pthread_self() -(unsigned int) &ft);
	__asm__(
	"subl %%ecx, %%esp\n"
	"movl %%esp, %%edi\n"
	"rep movsb\n"
	"call *%%eax\n"
	:
	:"a"(ft->f),"c"(ft->argSize), "S"(ft->esp)
	:"%edi");
}


#else      /* -----  not _PTHREAD  ----- */
#define typeof(x) x
#define push2stack(v){ switch(_INTSIZEOF(typeof(v))) {\
case 1: *(char*)(pcur) = v; break; \
case 2: *(short*)(pcur) = v; break; \
case 4: *(int*)(pcur) = v; break; \
case 8: *(long long*)(pcur) = v; break; \
}}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  thread_func_g
 *  Description:  the thread template for launching simple function,
 *                it copy the arguments from p->esp to the stack, then call the p->f;
 *  	  Input:  
 *       Output:
 *      Example:  thread_func_g
 * =====================================================================================
 */
kernel_ret thread_func_g(void*p){
	funcInfo_t* ft = (funcInfo_t*)p;
	unsigned int f = (unsigned int)ft->f;
	unsigned int argSize = (unsigned int)ft->argSize;
	unsigned int stack = (unsigned int)ft->esp;
	__asm{ 
			__asm push esi
			__asm push edi
			__asm mov eax, f
			__asm mov ecx,  argSize
			__asm mov esi, stack

			__asm sub esp, ecx
			__asm mov edi, esp
			__asm rep movsb
			__asm call eax

			__asm pop edi
			__asm pop esi
 
	}
}
#endif     /* -----  not _PTHREAD  ----- */

#define launchTemplateThread() \
create_thread(thread_func_g, &global_funcInfo);// /*thread_func_g(&global_funcInfo);*/
	
///////////////////// 0 args ////////////////////////////////////////////
#define slaunchArg0( ) {char* pcur= global_funcInfo.esp; \
	global_funcInfo.argSize =0;\
}\
launchTemplateThread();

#define slaunch0(sfunc) global_funcInfo.f = (void*) sfunc; slaunchArg0

///////////////////// 1 args ////////////////////////////////////////////
#define slaunchArg1( a00) {char* pcur= global_funcInfo.esp; \
	push2stack(a00); pcur += _INTSIZEOF(typeof(a00));\
	global_funcInfo.argSize = pcur - global_funcInfo.esp;\
}\
launchTemplateThread();

#define slaunch1(sfunc) global_funcInfo.f = (void*) sfunc; slaunchArg1

///////////////////// 2 args ////////////////////////////////////////////
#define slaunchArg2( a00, a01) {char* pcur= global_funcInfo.esp; \
	push2stack(a00); pcur += _INTSIZEOF(typeof(a00));\
	push2stack(a01); pcur += _INTSIZEOF(typeof(a01));\
	global_funcInfo.argSize = pcur - global_funcInfo.esp;\
}\
launchTemplateThread();

#define slaunch2(sfunc) global_funcInfo.f = (void*) sfunc; slaunchArg2

///////////////////// 3 args ///////////////////////////////////////////

#define slaunchArg3( a00, a01, a02) {char* pcur= global_funcInfo.esp; \
	push2stack(a00); pcur += _INTSIZEOF(typeof(a00));\
	push2stack(a01); pcur += _INTSIZEOF(typeof(a01));\
	push2stack(a02); pcur += _INTSIZEOF(typeof(a02));\
	global_funcInfo.argSize = pcur - global_funcInfo.esp;\
}\
launchTemplateThread();

#define slaunch3(sfunc) global_funcInfo.f = (void*) sfunc; slaunchArg3
	
/***************************************************************************************
 *
 *the Launcher end
 *
 **************************************************************************************/

#endif   /* ----- #ifndef THREADLAUNCHER_HEADER__INC  ----- */
