#ifndef __MDTIME_HEADER__
#define __MDTIME_HEADER__
#ifdef WIN32
#include "windows.h"
const int MICRO = 1000;
static double mdtime(int id)
{
	static double startT,stopT;
	LARGE_INTEGER time_1, time_fre;
	if(id==0)
	{
		QueryPerformanceCounter(&time_1);
		QueryPerformanceFrequency(&time_fre);
		startT = (double)time_1.QuadPart * MICRO / (double)time_fre.QuadPart;
		return 0.0;
	}
	else 
	{
		QueryPerformanceCounter(&time_1);
		QueryPerformanceFrequency(&time_fre);
		stopT = (double)time_1.QuadPart * MICRO / (double)time_fre.QuadPart;
		return (stopT - startT);
	}
}
#else
#include <sys/time.h>
static double mdtime(int id)
{
	static struct timeval _tstart ,_tend;
	struct timezone tz;
	if(id==0)
	{
		gettimeofday(&_tstart, &tz);
		return 0;
	}
	else 
	{
		double t1,t2;
		gettimeofday(&_tend, &tz);
		t1=(double)_tstart.tv_sec + (double)_tstart.tv_usec/(1000*1000);
		t2 =  (double)_tend.tv_sec + (double)_tend.tv_usec/(1000*1000);
		return (t2-t1);
	}

}

static double pmdtime(int id)
{
	static struct timeval _tstart ,_tend;
	struct timezone tz;
	if(id==0)
	{
		gettimeofday(&_tstart, &tz);
		return 0;
	}
	else 
	{
		double t1,t2;
		gettimeofday(&_tend, &tz);
		t1=(double)_tstart.tv_sec + (double)_tstart.tv_usec/(1000*1000);
		t2 =  (double)_tend.tv_sec + (double)_tend.tv_usec/(1000*1000);
		printf("time:%f\n",t2-t1);
		return (t2-t1);
	}

}

static double mdtime1(int id)
{
	static struct timeval _tstart ,_tend;
	struct timezone tz;
	if(id==0)
	{
		gettimeofday(&_tstart, &tz);
		return 0;
	}
	else
	{
		double t1,t2;
		gettimeofday(&_tend, &tz);
		t1=(double)_tstart.tv_sec + (double)_tstart.tv_usec/(1000*1000);
		t2 =  (double)_tend.tv_sec + (double)_tend.tv_usec/(1000*1000);
		return (t2-t1);
	}

}
inline static double dtime()
{
	struct timeval _tstart ;
	gettimeofday(&_tstart, NULL);
	return (double)_tstart.tv_sec + (double)_tstart.tv_usec/(1000*1000);
}
#endif

#endif
