/*
 * =====================================================================================
 *       Filename:  simpleQsort.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/06/2010 09:23:27 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhenghua Dai , djx.zhenghua@gmail.com
 *        Company:  
 *
 * =====================================================================================
 * =====================================================================================
 */
#include <stdio.h>
typedef int* pint;
typedef unsigned int T;
T* header = 0;
#include "threadWrapper.h"
#include "threadPool.h"
THREAD_VAR ;
THREAD_POOL_VAR;

void swap(T*a, T* b){
    T t = *a;
    *a = *b;
    *b = t;
}

T* partition(T* begin, T* end)
{
   T pivot = *end;
   while(begin < end){
       while((begin < end)&&(*begin < pivot)) begin ++;
       if(begin == end) break;
       *end = * begin;
       end --;
       while((begin < end) && ( *end> pivot) ) end --;
       if(begin == end) break;
       *begin = *end;
       begin++;
   }
   *begin = pivot;
   return begin;
}


void simpleSort(T* begin, T* end)
{
    for(int i=end - begin; i>0 ; i--){
        for( int j=0; j<  i; j++){
            if( begin[j]> begin[j+1])
            swap( begin + j, begin + j +1);
        }
    }
}

__kernel simpleQsort(T* begin, T* end)
{
    if(begin >=end) return ;
    if(end - begin< 7)
        return simpleSort(begin, end);
    T* middle = partition(begin, end);
             // simpleQsort(begin, middle-1);
    int my_current_thread =   dlaunch2(simpleQsort)((int*)begin, (middle-1));
    simpleQsort(middle+1, end);
    dsync(my_current_thread );
    return ;
}


void simpleQsort(T* begin, unsigned int size)
{
    header =begin;
    simpleQsort(begin, begin+size-1);
    printf("sort end\n");
}

void initThread()
{
    initGroup2(1, 2);
}
