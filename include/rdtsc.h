#ifndef RDTSC_HEADER
#define RDTSC_HEADER

#if defined(__GNUC__)

#define rdtsc(low,high) \
__asm__ __volatile__("rdtsc" : "=a" (low), "=d" (high));

#define rdtsc1(t) \
__asm__ __volatile__("rdtsc" : "=a" (*(int*)&t), "=d" (*(((int*)&t)+1)));

#define nasm0(op) __asm__( #op)
#else 
//#elif defined(_MSC_VER)
#define rdtsc(low32, high32) \
__asm rdtsc \
__asm mov low32, eax \
__asm mov high32, edx 

#define rdtsc1(t) \
__asm rdtsc \
__asm mov t, eax \
__asm mov t+4, edx 

#define nasm0(x) __asm x

#endif

#if  0 
typedef union {
	unsigned long long  u64;
	struct{
		unsigned int low;
		unsigned int high;
	};
} U64;
#define diffTime(start,end) ((end.u64)-(start.u64))
#define cast2u64(x) x.u64

#else 
typedef unsigned long long U64;
#define diffTime(start,end) (end)-(start)
#define cast2u64(x) x
#endif

#define timens(x) timenamespace ## x


//static inline unsigned long long getrdtsc()
//{
//	U64 a;
//	rdtsc(a.low, a.high);
//	return a.u64;
//}

static inline U64  getrdtsc(){
	nasm0(rdtsc);
}
static U64 startT, endT;
static inline U64 startTime(){
		//rdtsc1(startT);
		startT = getrdtsc();
		return startT;
}

static inline U64 endTime(){
		//rdtsc1(endT);
		endT = getrdtsc();
		return (U64) diffTime(startT,endT);
}

static inline U64 getTime(){
	return (U64) diffTime(startT,endT);
}

static inline double mdtime(int id){
	static U64 startT, endT;
	if(id){
		rdtsc1(endT);
		return (double)(diffTime(startT,endT));
	}else{
		rdtsc1(startT);
		return (double) cast2u64(startT);
	}
}

static inline double pdtime(int id){
	static U64 startT, endT;
	if(id){
		rdtsc1(endT);
		printf("time:%f\n",diffTime(startT,endT));
		return (double)(diffTime(startT,endT));
	}else{
		rdtsc1(startT);
		return (double) cast2u64(startT);
	}
}
static double getFrequency()
{
	double t3;
	U64 startT, endT;
	rdtsc1(startT);
	sleep(1);
	rdtsc1(endT);
	t3=  (double)(diffTime(startT,endT));
	return t3;
}

static double RDTSC_CORE_FREQ = 0;
static inline double mdgetSeconds(double c)
{
	if (RDTSC_CORE_FREQ ==0) RDTSC_CORE_FREQ = getFrequency();
	return c/ RDTSC_CORE_FREQ;
}

#endif
