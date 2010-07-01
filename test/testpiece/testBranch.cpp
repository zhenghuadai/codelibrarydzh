/*
 * =====================================================================================
 *       Filename:  testBranch.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/01/2010 03:40:41 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhenghua Dai , djx.zhenghua@gmail.com
 *        Company:  
 *
 * =====================================================================================
 *     Copyright (c) 2010, Zhenghua Dai. All rights reserved.
 * =====================================================================================
 */
#include "rdtsc.h"
#include <xmmintrin.h>
#include "align.h"

int testC(int*x, int* S, int* w, int cv)
{
    int sum =0;
    if( x[0] >= 0 )
        sum += (S[x[0]] - cv)*w[0];
    if( x[1] >= 0 )
        sum += (S[x[1]] - cv)*w[1];
    if( x[2] >= 0 )
        sum += (S[x[2]] - cv)*w[2];
    if( x[3] >= 0 )
        sum += (S[x[3]] - cv)*w[3];
    if( x[4] >= 0 )
        sum += (S[x[4]] - cv)*w[4];
    if( x[5] >= 0 )
        sum += (S[x[5]] - cv)*w[5];
    if( x[6] >= 0 )
        sum += (S[x[6]] - cv)*w[6];
    if( x[7] >= 0 )
        sum += (S[x[7]] - cv)*w[7];
    return sum;
}

int testSSE(int* x, int* S, int* w, int cv)
{
    int sum = 0;
    __ALIGN__(16) int tmpx[8];
    __m128i sumV;
    __m128i zeroV= _mm_xor_si128(zeroV, zeroV);
    __m128i xV = _mm_load_si128((__m128i* const)x);
    __m128i cmpV = _mm_cmplt_epi32(xV, zeroV);
    xV = _mm_or_si128(xV, cmpV);
    _mm_store_si128((__m128i* const)tmpx, xV);

    xV = _mm_load_si128((__m128i* const)x + 1);
    cmpV = _mm_cmplt_epi32(xV, zeroV);
    xV = _mm_or_si128(xV, cmpV);
    _mm_store_si128((__m128i* const)tmpx + 1, xV);
    S[-1] = cv;
    sum += (S[tmpx[0]] - cv)*w[0];
    sum += (S[tmpx[1]] - cv)*w[1];
    sum += (S[tmpx[2]] - cv)*w[2];
    sum += (S[tmpx[3]] - cv)*w[3];
    sum += (S[tmpx[4]] - cv)*w[4];
    sum += (S[tmpx[5]] - cv)*w[5];
    sum += (S[tmpx[6]] - cv)*w[6];
    sum += (S[tmpx[7]] - cv)*w[7];
    return sum;
}

int main()
{
    __ALIGN16__  int x[16];
    __ALIGN16__    int S[16];
    __ALIGN16__   int w[8];
    int cv = 20;;
    for(int i=0;i<8;i++){
        x[i] = rand()%8 * (rand()%2? -1:1);
        S[i] = rand();
        w[i] = rand()%100;
    }
    startTime();
    for(int i=0;i<10000000;i++)
        testC(x, S ,w, i);
    printf("%d\n",stopTime());

    startTime();
    for(int i=0;i<10000000;i++)
        testSSE(x, S ,w, i);
    printf("%d\n",stopTime());
}
