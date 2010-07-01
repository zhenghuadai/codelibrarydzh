#define fArgTypename(f) f##Arg_t
#define structname(a, b, c)  struct ## a ## b ## c

#define AAAint(x) int
#define BBBint(x) x 
#define AAA(a) AAA##a
#define BBB(a) BBB##a  // BBB(int(a))
#define structname_mid(a, b, c) structname(a, b, c)
#define structname_pre(a, b, c) structname_mid( AAA(a), AAA(b), AAA(c)) 

#define definethreadf(name, arg) \
typedef structname_pre arg name##Arg_t;\
tfunc_ret name(void*p)

#define defineArg(a, b, c)\
typedef struct{\
		a arg1;	\
		b arg2;	\
		c arg3;	\
} structname(a,b,c);


#define poptArg( a, b,c)\
AAA(a) BBB(a) = ((structname_pre(a,b,c)*)p)->arg1;\
AAA(b) BBB(b) = ((structname_pre(a,b,c)*)p)->arg2;\
AAA(c) BBB(c) = ((structname_pre(a,b,c)*)p)->arg3;\

#define pushtArg(a, b, c)\
pArg->arg1=a;\
pArg->arg2=b;\
pArg->arg3=c;\
}\
}

#define launchfunc( pfuncKernel) c[tid].func = pfuncKernel; {\
fArgTypename(pfuncKernel)* pArg = (fArgTypename(pfuncKernel)*)&kArg[tid];  c[tid].arg= (void*)pArg; pushtArg 
#define launch(tid0) { int tid = tid0; launchfunc 
			
#if 0
#define structname2(at,a, bt,  b,ct, c)  struct ## at ## bt ## ct
#define definethreadf0(name, para1t, para1, para2t, para2, para3t, para3)\
typedef structname(para1t, para2t, para3t) name##Arg_t; \
tfunc_ret name(void* p)

#define definethreadf2(name, arg) \
typedef structname2 arg name##Arg_t;\
tfunc_ret name(void*p)
#define launch(tid0, pfuncKernel) { int tid = tid0; c[tid].func = pfuncKernel; c[tid].arg= (void*)&kArg[tid]; pushtArg

#define poptArg( at,a, bt,b, ct, c)\
at a = ((structname(at,bt,ct)*)p)->arg1;\
bt b = ((structname(at,bt,ct)*)p)->arg2;\
ct c = ((structname(at,bt,ct)*)p)->arg3;\

#define poptArg0(type, a, b, c)\
a = ((type*)p)->arg1;\
b = ((type*)p)->arg2;\
c = ((type*)p)->arg3;\


#endif
