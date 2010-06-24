#ifndef __MDTIME_HEADER__
#define __MDTIME_HEADER__
typedef unsigned long long U64;
U64 cpu_freqency=0;
	 
#if defined(_MSC_VER)	 
 
#include "windows.h"
const int MICRO = 1000;

U64 getClock(){
    LARGE_INTEGER time_1;
    QueryPerformanceCounter(&time_1);
    return time_1.QuadPart;
}

static double mdtime(int id)
{
    static double startT,stopT; 
    static LARGE_INTEGER time_fre;
    if(id==0)
    {
        QueryPerformanceFrequency(&time_fre);
        startT = (double)getClock() * MICRO / (double)(unsigned long long)time_fre.QuadPart;
        return 0.0;
    }
    else 
    {
        stopT = (double)getClock()* MICRO / (double)(unsigned long long)time_fre.QuadPart;
        return (stopT - startT);
    }
}
#elif defined(__GNUC__)
#include <sys/time.h>
#include <stdio.h>
U64 getClock(){
    static struct timeval _t;
    struct timezone tz;
    gettimeofday(&_t, &tz);
    return (((U64) _t.tv_sec)*1000 + ((U64) _t.tv_usec)/1000);
}

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
        t1=(double)_tstart.tv_sec*1000 + (double)_tstart.tv_usec/(1000);
        t2 =  (double)_tend.tv_sec*1000 + (double)_tend.tv_usec/(1000);
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
        t1=(double)_tstart.tv_sec *1000+ (double)_tstart.tv_usec/(1000);
        t2 =  (double)_tend.tv_sec*1000 + (double)_tend.tv_usec/(1000);
        printf("time:%f ms\n",t2-t1);
        return (t2-t1);
    }

}
#endif

#endif
