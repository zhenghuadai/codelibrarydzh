/*
 * =====================================================================================
 *       Filename:  testrcp.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/05/2010 01:27:28 PM
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
#include "align.h"
#include <stdio.h>
#include <xmmintrin.h>

int main()
{
    __ALIGN16__ float a[4];
    __ALIGN16__ float rcp[4]={0,0,2,3};
    __ALIGN16__ float mask[4]={1.0,1.0,1.0,1.0};
    __m128 aV;
    __m128 rcpV;
    __m128 maskV;

    a[0]=0.0; a[1] = 1; a[2]=2; a[3] =3;
    printf("%f\n", rcp[0]);
    aV = _mm_load_ps(a);
    maskV = _mm_cmpeq_ps(aV, _mm_load_ps(rcp));
    rcpV = _mm_rcp_ps(aV);
    rcpV = _mm_and_ps(aV,maskV);
    _mm_store_ps(rcp, rcpV);
    printf("%f %f %f %f \n", rcp[0],rcp[1], rcp[2],rcp[3]);
    printf("%0x\n", rcp[0]);
}
