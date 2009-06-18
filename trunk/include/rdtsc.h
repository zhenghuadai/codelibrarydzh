#ifndef rdtsc

#ifndef rdtscfreq
#define rdtscfreq 2.1280493e9
#endif
#define rdtsc(low,high) \
__asm__ __volatile__("rdtsc" : "=a" (low), "=d" (high))



typedef union {
	unsigned long long  u64;
	struct{
		unsigned int low;
		unsigned int high;
	};
} _U64;
static inline unsigned long long getrdtc()
{
	_U64 a;
	rdtsc(a.low, a.high);
	return a.u64;
}

static inline double mdtime(int id){
	static _U64 startT, endT;
	if(id){
		rdtsc(endT.low,endT.high);
		return (double)(endT.u64 - startT.u64);
	}else{
		rdtsc(startT.low,startT.high);
	return 0.0;
	}
}

static inline  double rdtscdiff(unsigned int low1,unsigned int high1,unsigned int low2,unsigned int high2)
{
	const  double MAXintplus1 = 4294967296.0;
	unsigned int low,high;
	if (low2<low1) {
	low = 0xffffffff - low1 + low2;
	high = high2 - high1 -1;
	}
	else {
	high = high2 - high1;
	low = low2 - low1;
	}
	return (double)high * MAXintplus1 + (double)low ;
}

static inline double mdtime4(int id)
{
	static unsigned int high0,low0,high1,low1;
	if(id){
		rdtsc(low1,high1);
	        return rdtscdiff(low0,high0,low1,high1)/rdtscfreq;	
	}
	else{
		rdtsc(low0,high0);
		return 0.0;
	}
}
static inline double mdtime2(int id)
{
	static unsigned int high0,low0,high1,low1;
	if(id){
		rdtsc(low1,high1);
	        return rdtscdiff(low0,high0,low1,high1)/rdtscfreq;	
	}
	else{
		rdtsc(low0,high0);
		return 0.0;
	}
}
#endif
