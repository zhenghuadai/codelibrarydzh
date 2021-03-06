#ifndef __MACRO_ASM_HEADER__
#define __MACRO_ASM_HEADER__
/*********************************************************
 *E 	:  32-bit GRP 
 *R   	:  64-bit GRP
 *m 	:  memory
 *M 	:  MMX 
 *X 	:  XMM
 *i 	:  immediate
 *F 	:  float 
 *D 	:  double
 * ******************************************************/
/*********************************************************
//! pay attention: masm a, b is  b->a;
//! pay attention: masm a, b is  b->a;
//! pay attention: masm a, b is  b->a;
//! pay attention: masm a, b is  b->a;
//! pay attention: masm a, b is  b->a;
//! pay attention: masm a, b is  b->a;
//! pay attention: masm a, b is  b->a;
//! pay attention: masm a, b is  b->a;
//! pay attention: masm a, b is  b->a;
//! pay attention: masm a, b is  b->a;
//! pay attention: masm a, b is  b->a;
//! pay attention: masm a, b is  b->a;
//! pay attention: masm a, b is  b->a;
//! pay attention: masm a, b is  b->a;
//! pay attention: masm a, b is  b->a;
//! pay attention: masm a, b is  b->a;
//! pay attention: masm a, b is  b->a;
 * ******************************************************/
typedef enum {
R2R,
E2E,
X2X,
M2M,
m2R,
m2E,
m2EDA,
m2M,
m2X,
R2m,
E2m,
M2m,
X2m,
m2F,
F2m,
F2F,
mXm,

} instr_t;

#ifdef X64
#define gax rax
#define gbx rbx
#define gcx rcx
#define gdx rdx
#define gsi rsi
#define gdi rdi
#else 
#define gax eax
#define gbx ebx
#define gcx ecx
#define gdx edx
#define gsi esi
#define gdi edi
#endif


#define Str(x) #x
#define Str2(x) Str(x) 

/***********************************************************************/
#ifdef  INTEL_ASM
/***********************************************************************/

/***********************************************************************
 * intel ASM
 * *********************************************************************/
#define __ALIGN16__ __declspec(align(16))
#define __ALIGN__ __declspec(align(128))
#define addrsufix 
#define baddrsufix  
#define waddrsufix 
#define daddrsufix 
#define qaddrsufix 
#define xaddrsufix 
#define addrptr 
#define baddrptr byte ptr
#define waddrptr word ptr
#define daddrptr dword ptr
#define qaddrptr mmwrod ptr
#define xaddrptr xmmword ptr
/*---------------mcode----------------------------------*/

#define __mcode__R2R(x, a, b)       __asm x a, b
#define __mcode__E2E(x, a, b)       __asm x a, b
#define __mcode__m2E(x, e, m)       __asm x e, dword ptr m
#define __mcode__m2R(x, r, m)       __asm x r, qword ptr m
#define __mcode__E2m(x, m, e)       __asm x dword ptr m, e
#define __mcode__R2m(x, m, r)       __asm x qword ptr m, r
                                    
#define __mcode__E2EDA(x, e)        __asm x e 
#define __mcode__m2EDA(x, m)        __asm x dword ptr m 

#define __mcode__m2F(x,  m)         __asm x dword ptr m 
#define __mcode__F2m(x,  m)         __asm x dword ptr m 
#define __mcode__m2D(x,  m)         __asm x qword ptr m 
#define __mcode__D2m(x,  m)         __asm x qword ptr m 
#define __mcode__F2F(x, a, b)       __asm x st(a), st(b)
#define __mcode__D2D(x, a, b)       __mcode__F2F(x, a, b) 
#define __mcode__F2E(x,m)           __asm x dword ptr m
                                     
#define __mcode__X2X(x, a, b)       __asm x a, b 
#define __mcode__m2X(x, a, b)       __asm x a, b 
#define __mcode__X2m(x, a, b)       __asm x a, b 
#define __mcode__Xi2X(x, a, b, imm) __asm x a, b , imm
#define __mcode__mi2M(x, a, b, imm) __asm x a, b , imm
#define __mcode__mi2X(x, a, b, imm) __asm x a, b , imm
/**-----------__masm------------------------------------*/

#define masm__(x) 					__asm x
#define masm__R2R(x, a, b)       __asm __mcode__R2R(x, a, b) 
#define masm__E2E(x, a, b)       __asm __mcode__E2E(x, a, b)
#define masm__m2E(x, e, m)       __asm __mcode__m2E(x, e, m)
#define masm__m2R(x, r, m)       __asm __mcode__m2R(x, r, m)
#define masm__E2m(x, m, e)       __asm __mcode__E2m(x, m, e)
#define masm__R2m(x, m, r)       __asm __mcode__R2m(x, m, r)
                                                             
#define masm__E2EDA(x, e)     __asm __mcode__E2EDA(x, e)
#define masm__m2EDA(x, m)     __asm __mcode__m2EDA(x, m)
                                                             
#define masm__m2F(x,  m)         __asm __mcode__m2F(x,  m)  
#define masm__F2m(x,  m)         __asm __mcode__F2m(x,  m)  
#define masm__m2D(x,  m)         __asm __mcode__m2D(x,  m)  
#define masm__D2m(x,  m)         __asm __mcode__D2m(x,  m)  
#define masm__F2F(x, a, b)       __asm __mcode__F2F(x, a, b)
#define masm__D2D(x, a, b)       __asm __mcode__D2D(x, a, b)
#define masm__F2E(x,m)           __asm __mcode__F2E(x,m)    
                                                       
#define masm__X2X(x, a, b)       __asm  __mcode__X2X(x, a, b)
#define masm__m2X(x, a, b)       __asm  __mcode__m2X(x, a, b)
#define masm__X2m(x, a, b)       __asm  __mcode__X2m(x, a, b)
#define masm__Xi2X(x, a, b, imm) __asm  __mcode__Xi2X(x, a, b, imm)
#define masm__mi2M(x, a, b, imm) __asm  __mcode__mi2M(x, a, b, imm)
#define masm__mi2X(x, a, b, imm) __asm  __mcode__mi2X(x, a, b, imm)

/*---------------------------Addressing------------------------------------------------*/
#define memAddr4(off, base, var, typelen) [base+var*typelen+off]
#define memAddr3(off, base, var)          [base+var+off] 
#define memAddr2(off, base)               [base+off]
#define memAddr1(base)                    [base]

#define __asmblock __asm{
#define __asmblockEnd }; 
/****************************************************************************************************************************/
/****************************************************************************************************************************/
/*****************************************************************INTEL_ASM**************************************************/
/****************************************************************************************************************************/
/****************************************************************************************************************************/
#else  /*************************************************#ifdef  INTEL_ASM***************************************************/
/****************************************************************************************************************************/
/****************************************************************************************************************************/
/*****************************************************************GNU ASM****************************************************/
/****************************************************************************************************************************/
/****************************************************************************************************************************/

/***********************************************************************
 * GNU ASM
 * *********************************************************************/
#define eax_ a
#define ebx_ b
#define ecx_ c
#define edx_ d
#define esi_ S
#define edi_ D
#define A(r) r##_
#define inRistrict(x) =##x
#define ioRistrict(x) +##x
#ifdef X64
#define masm__ProtectReg()      __asm__("pushq %rax; pushq %rbx; pushq %rcx; pushq %rdx;");
#define masm__RecoverReg()      __asm__("popq  %rdx; popq  %rcx; popq  %rbx; popq  %rax;");
#else 
#define masm__ProtectReg()      __asm__("pushl %eax; pushl %ebx; pushl %ecx; pushl %edx;");
#define masm__RecoverReg()      __asm__("popl  %edx; popl  %ecx; popl  %ebx; popl  %eax;");
#endif 

#define __ALIGN16__ __attribute__((aligned(16)))
#define __ALIGN__ __attribute__((aligned(128)))
#define masm__(x) __asm(Str(x):); 
#define addrsufix 
#define baddrsufix b 
#define waddrsufix w
#define daddrsufix l
#define qaddrsufix q
#define xaddrsufix 
#define addrptr 
#define baddrptr
#define waddrptr
#define daddrptr
#define qaddrptr
#define xaddrptr
/*-------------------__mcode__---------------------------------------------------------*/
#define __mcode__R2R(x, a, b)        Str(x) "q %%" Str(b) ", %%" Str(a) "; "
#define __mcode__E2E(x, a, b)        Str(x) "l %%" Str(b) ", %%" Str(a) "; "
#define __mcode__m2E(x, e, m)        Str(x) "l (%0), %%" Str(e) "; "
#define __mcode__m2R(x, r, m)        Str(x) "q (%0), %%" Str(r) "; "
#define __mcode__E2m(x, m, e)        Str(x) "l %%" Str(e) ",(%0) ; "
#define __mcode__R2m(x, m, r)        Str(x) "q %%" Str(r) ",(%0) ; "

#define __mcode__E2EDA(x, e)         Str(x) "l %%" Str(e) ";"
#define __mcode__m2EDA(x, m)         Str(x) "l (%0);"

#define __mcode__m2F(x, m)           Str(x) "s (%0);"
#define __mcode__F2m(x, m)           Str(x) "s (%0);"
#define __mcode__m2D(x, m)           Str(x) "l (%0);"
#define __mcode__D2m(x, m)           Str(x) "l (%0);"
#define __mcode__F2F(x, a, b) 	   	 Str(x) "  %%st(" Str(a) "), %%st(" Str(b) ");"
#define __mcode__D2D(x, a, b) 	     __mcode__F2F(x, a, b)	
#define __mcode__F2E(x,m) 		   	 Str(x) "l  %0;"

#define __mcode__X2X(x, a, b)        Str(x) " %%" Str(b) ", %%" Str(a) "; " 
#define __mcode__m2X(x, a, m)        Str(x) " (%0), %%" Str(a) "; " 
#define __mcode__X2m(x, m, b)        Str(x) " %%" Str(b) ",(%0); " 
#define __mcode__Xi2X(x, a, b,imm)   Str(x) " $" Str(imm) ", %%" Str(b) ", %%" Str(a) "; " 
#define __mcode__mi2M(x, a, m,imm)   Str(x) " $" Str(imm) ", (%0), %%" Str(a) "; " 
#define __mcode__mi2X(x, X, m,imm)   Str(x) " $" Str(imm) ", (%0), %%" Str(X) "; " 
/*--------------------masm__-----------------------------------------------------------*/

#define masm__R2R(x, a, b)       __asm__(__mcode__R2R(x, a, b) :::"%"Str(a),"%"Str(b));
#define masm__E2E(x, a, b)       __asm__(__mcode__E2E(x, a, b) :::"%"Str(a),"%"Str(b));
//#define masm__m2E(x, e, m)       __asm__(__mcode__m2E(x, e, m) ::"r"(m):"%"Str(e));
#define masm__m2E(x, e, m)       __asm__(" " ::Str2(A(e))(m):);
#define masm__m2R(x, r, m)       __asm__(__mcode__m2R(x, r, m) ::"r"(m):"%"Str(r));
#define masm__E2m(x, m, e)       __asm__(__mcode__E2m(x, m, e) ::"r"(m):"%"Str(e));
#define masm__R2m(x, m, r)       __asm__(__mcode__R2m(x, m, r) ::"r"(m):"%"Str(r));

#define masm__E2EDA(x, e) 	     __asm__(__mcode__E2EDA(x, e)  :::"%edx", "%eax","%"Str(e));
#define masm__m2EDA(x, m) 	     __asm__(__mcode__m2EDA(x, m)  ::"r"(m):"%edx", "%eax");

#define masm__m2F(x, m)          __asm__(__mcode__m2F(x,m)     ::"r"(m):);
#define masm__F2m(x, m)          __asm__(__mcode__F2m(x,m)     ::"r"(m):);
#define masm__m2D(x, m)          __asm__(__mcode__m2D(x, m)    ::"r"(m):);
#define masm__D2m(x, m)          __asm__(__mcode__D2m(x, m)    ::"r"(m):);
#define masm__F2F(x, a, b) 	     __asm__(__mcode__F2F(x, a, b) :::);
#define masm__D2D(x, a, b) 	     __asm__(__mcode__D2D(x, a, b) :::);
#define masm__F2E(x,m) 		     __asm__(__mcode__F2E(x,m) 	::"m"(m):);

#define masm__X2X(x, a, b)       __asm__(__mcode__X2X(x, a, b)      :::);
#define masm__m2X(x, a, m)       __asm__(__mcode__m2X(x, a, m)      ::"r"(m):);
#define masm__X2m(x, m, b)       __asm__(__mcode__X2m(x, m, b)      ::"r"(m):);
#define masm__Xi2X(x, a, b,imm)  __asm__(__mcode__Xi2X(x, a, b,imm) :::);
#define masm__mi2M(x, a, m,imm)  __asm__(__mcode__mi2M(x, a, m,imm) ::"r"(m):);
#define masm__mi2X(x, X, m,imm)  __asm__(__mcode__mi2X(x, X, m,imm) ::"r"(m):);
/*---------------------------Addressing------------------------------------------------*/

#define memAddr4(off, base, var, typelen) Str(off) "(%%" Str(base) ",%%" Str(var) "," Str(typelen) ")"
#define memAddr3(off, base, var) Str(off) "(%%" Str(base) ",%%" Str(var) ")"
#define memAddr2(off, base) Str(off) "(%%" Str(base) ")"
#define memAddr1(base) "(%%" Str(base) ")"

#define LoadL4(off, base, var, typelen, dst) \
"movl " memAddr4(off, base, var, typelen) ", %%" Str(dst) ";"
//!LoadL4(8,rsi, rbx, 4, eax) == movl 8(rsi, rbx ,4) eax == movl rsi+rbx*4+8

#define LoadL3(off, base, var, dst) \
"movl " memAddr3(off, base, var) ", %%" Str(dst) ";"
//!LoadL3(8,rsi, rbx, eax) == movl 8(rsi, rbx ) eax

#define LoadL2(off, base, dst) \
"movl " memAddr2(off, base) ", %%" Str(dst) ";"
//!LoadL2(8,rsi, eax) == movl 8(rsi) eax

#define StoreL4(off, base, var, typelen, dst) \
"movl " "%%" Str(dst) ","   memAddr4(off, base, var, typelen) ";"
//!LoadL4(8,rsi, rbx, 4, eax) == movl 8(rsi, rbx ,4) eax == movl rsi+rbx*4+8

#define StoreL2(off, base, src) \
"movl "  "%%" Str(src) ","  memAddr2(off, base) ";"
//!StoreL2(8,rsi,eax ) == movl eax, 8(rsi) 

#define CLFLUSH3(off, base, var) \
"clflush " memAddr3(off, base, var) ";"

#define CLFLUSH2(off, base) \
"clflush " memAddr2(off, base) ";"

#define __asmx(x) Str(x) ";"
/**
 * (edx, eax) - (ebx, ecx)
 *subl ecx, eax 
 *sbbl ebx, edx 
 * */
#define __gcode_(x) Str(x) ";"
#define __gcode_e(x, a)      Str(x) "l %%" Str(a) ";"
#define __gcode_e2e(x, a, b) Str(x) "l %%" Str(a) ", %%" Str(b) ";"
#define __gcode_m2e(x, e, b) Str(x) "l (%%" Str(e) ")," Str(b) ";"
#define __gcode_e2m(x, a, r) Str(x) "l %%" Str(a) ",(%%" Str(r) ");" 

#ifdef X64
#define __gcode_g(x, a)      Str(x) "q %%" Str(a) ";"
#define __gcode_g2g(x, a, b) Str(x) "q %%" Str(a) ", %%" Str(b) ";"
#define __gcode_i2g(x, a, b) Str(x) "q $" Str(a) ", %%" Str(b) ";"
#define __gcode_m2g(x, g, b) Str(x) "q (%%" Str(g) ")," Str(b) ";"
#define __gcode_r2m(x, a, r) Str(x) "q %%" Str(a) ",(%%" Str(r) ");" 
#else
#define __gcode_g(x, a)      Str(x) "l %%" Str(a) ";"
#define __gcode_g2g(x, a, b) Str(x) "l %%" Str(a) ", %%" Str(b) ";"
#define __gcode_i2g(x, a, b) Str(x) "l $" Str(a) ", %%" Str(b) ";"
#define __gcode_m2g(x, m, b) Str(x) "l (%%" Str(m) ")," Str(b) ";"
#endif

#define __asmblock __asm__(
#define __asmblockEnd ); 
#define masm0(x) __asm( Str(x));
/****************************************************************************************************************************/
/****************************************************************************************************************************/
/*****************************************************************GNU ASM****************************************************/
/****************************************************************************************************************************/
/****************************************************************************************************************************/
#endif/****************#ifdef  INTEL_ASM*************************************************************************************/
/****************************************************************************************************************************/
/*leave mov esp,ebp;pop ebp*/
/*ret (IP)←((SP)+1,(SP));  (SP)←(SP)+2*/
/*ret exp (IP)←((SP)+1,(SP))  (SP)←(SP)+2  (SP)←(SP)+D16*/
#endif
