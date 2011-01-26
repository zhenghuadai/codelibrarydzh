/**
 * =====================================================================================
 *       @file    mdtime.h
 *
 *       @brief   
 *
 *       @author  DAI ZHENGHUA (), djx.zhenghua@gmail.com
 *       @version 1.0
 *       @date    01/19/2011 08:15:42 PM
 *
 *       Revision none
 *       Compiler gcc
 *       Company  
 * =====================================================================================
 */
#ifndef __MDTIME_HEADER__
#define __MDTIME_HEADER__

#ifdef _cplusplus
#define DEFAULT(x) =x
#else
#define DEFAULT(x) 
#endif

#ifndef CLOCK_NUM
#define CLOCK_NUM 10
#endif

#define diffTime(start,end) ((end)-(start))
typedef unsigned long long U64;
static U64 cpu_freqency=0;
static U64 start_mSeconds[CLOCK_NUM], stop_mSeconds[CLOCK_NUM];

#ifdef __GNUC__ 
#include <sys/time.h>
#include <stdio.h>
inline U64 getClock(){
    struct timeval _t;
    struct timezone tz;
    gettimeofday(&_t, &tz);
    return (((U64) _t.tv_sec)*1000 + ((U64) _t.tv_usec)/1000);
}
#elif defined(_MSC_VER)
#include "windows.h"
inline U64 getClock(){
    LARGE_INTEGER time_1;
    QueryPerformanceCounter(&time_1);
    if(cpu_freqency == 0){
        LARGE_INTEGER freq_1;
        QueryPerformanceFrequency(&freq_1);
        cpu_frequency = freq_1.QuadPart;
    }
    return time_1.QuadPart * 1000 / cpu_freqency;
}
#endif
static inline U64 startTime(int cid  DEFAULT(0)){
		start_mSeconds[cid] = getClock();
		return start_mSeconds[cid];
}

static inline U64 stopTime(int cid DEFAULT(0)){
		stop_mSeconds[cid] = getClock();
		return (U64) diffTime(start_mSeconds[cid],stop_mSeconds[cid]);
}

static inline U64 getTime(int cid DEFAULT(0)){
	return (U64) diffTime(start_mSeconds[cid],stop_mSeconds[cid]);
}

static inline U64 pTime(int cid DEFAULT(0)){
    U64 t = diffTime(start_mSeconds[cid], stop_mSeconds[cid]);
    printf("time:%d\n", t);
	return t;
}



#if defined(_MSC_VER) 
const int MICRO = 1000;
static double mdtime(int id)
{
    static double start_mSeconds,stop_mSeconds;
    static LARGE_INTEGER time_1;
    LARGE_INTEGER time_fre;
    if(id==0)
    {
        QueryPerformanceFrequency(&time_1);
        start_mSeconds = (double)getClock() * MICRO / (double)time_fre.QuadPart;
        return 0.0;
    }
    else 
    {
        stop_mSeconds = (double)getClock()* MICRO / (double)time_fre.QuadPart;
        return (stop_mSeconds - start_mSeconds);
    }
}
#elif defined(__GNUC__) 
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
