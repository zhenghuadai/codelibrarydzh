#pragma once
#ifdef WIN32
#include "windows.h"
#define rdtsc(low,high) \
	__asm cpuid                 \
__asm rdtsc                 \
__asm mov dword ptr low,eax   \
__asm mov dword ptr high,edx

#else
#include "sys/time.h"
#define rdtsc(low,high) \
	__asm__ __volatile__("rdtsc" : "=a" (low), "=d" (high))

#endif
#define MICRO 1000000
#ifdef __cplusplus
class getTime
{
	public:
		getTime(void){};
		double start()
		{
#ifdef WIN32
			LARGE_INTEGER time_t, time_fre;
			QueryPerformanceCounter(&time_t);
			QueryPerformanceFrequency(&time_fre);
			startT = (double)time_t.QuadPart * MICRO / (double)time_fre.QuadPart;
#else
			struct timeval _tstart ;
			struct timezone tz;
			gettimeofday(&_tstart, &tz);	 
			startT = (double)_tstart.tv_sec + (double)_tstart.tv_usec/(1000*1000);
#endif
			return startT;
		}
		double stop()
		{
#ifdef WIN32
			LARGE_INTEGER time_t, time_fre;
			QueryPerformanceCounter(&time_t);
			QueryPerformanceFrequency(&time_fre);
			stopT = (double)time_t.QuadPart * MICRO / (double)time_fre.QuadPart;
#else
			struct timeval _tstart ;
			struct timezone tz;
			gettimeofday(&_tstart, &tz);	 
			stopT = (double)_tstart.tv_sec + (double)_tstart.tv_usec/(1000*1000);
#endif
			return stopT;
		}
		double time()
		{
			return (stopT - startT);
		}
		void ptime(char* msg="")
		{
			printf("%s %f", msg, stopT - startT);
		}
		void ptimen(char* msg="")
		{
			ptime(msg);
			printf("\n");
		}
public:
		void startTSC()
		{
			rdtsc(sL,sH);
		}
		void stopTSC()
		{
			rdtsc(eL,eH);
		}
		int getTSC()
		{
			return (eL-sL);
		}
		~getTime(void){};
	public:
		double startT;
		double stopT;
		union{
			struct{
				unsigned int sL,sH;
			};
			unsigned long long sHL;
		};
		union{
			struct{
				unsigned int eL,eH;
			};
			unsigned long long eHL;
		};

};
#endif
