/*
 * =====================================================================================
 *
 *       Filename:  binSort.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhenghua Dai (Zhenghua Dai), djx.zhenghua@gamil.com
 *        Company:  dzh
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
//#define __ALIGN__ __declspec(align(128))
#define __ALIGN__ __attribute__((aligned(128)))
#include <xmmintrin.h>
typedef unsigned int u32;
static u32 buf[65536*2];
static inline void swapPtr(u32*& a, u32*& b)
{
	u32* tmp = a;
	a = b;
	b = tmp;
}
void copyBack(u32* dst, u32* src,  unsigned int n)
{
	for(int i=0;i< n;i++)
		dst[i] = src[i];
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  binSort_binary1
 *  Description:
 *  	  Input:  
 *       Output:
 *      Example:  binSort_binary1
 * =====================================================================================
 */
void binSort_binary1(u32 *a,  unsigned int n)
{
	unsigned 	int iteration = 1;
	u32* src = a;
	u32* dst = buf;
	for(iteration = 1; iteration !=0; iteration = iteration << 1)
	{
		u32* pStart = dst;
		u32* pEnd   = dst + n -1;
		for(int i=0;i<n;i++){
			u32 curEle = src[i];
			u32 mask = curEle & iteration;
			if(mask ==0){
				*pStart = curEle;
				pStart ++;
			}else{
				*pEnd= curEle;
				pEnd --;
			}
		}
		swapPtr(src, dst);
	}
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  binSort_binary2
 *  Description:
 *  	  Input:  
 *       Output:
 *      Example:  binSort_binary2
 * =====================================================================================
 */
void binSort_binary2(u32 *a,  unsigned int n)
{
	unsigned 	int iteration = 1;
	u32* src = a;
	u32* dst = buf;
	for(iteration = 1; iteration !=0; iteration = iteration << 1)
	{
		u32* pStart = dst;
		int part2 = 0;

		for(int i=0;i<n;i++){
			u32 curEle = src[i];
			u32 mask = curEle & iteration;
			if(mask ==0) part2 ++;
		}

		u32* pPart2 = dst + part2;
		for(int i=0;i<n;i++){
			u32 curEle = src[i];
			u32 mask = curEle & iteration;
			if(mask ==0){
				*pStart = curEle;
				pStart ++;
			}else{
				*pPart2= curEle;
				pPart2++;
			}
		}
		swapPtr(src, dst);
	}
	if(a != src)
		copyBack(a, src, n);
}
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  binSort_byte
 *  Description:
 *  	  Input:  
 *       Output:
 *      Example:  binSort_byte
 * =====================================================================================
 */
static void binSort_byte_one_radix(u32 *src, u32* dst,  unsigned int n, int shiftR)
{
	__ALIGN__ unsigned int index[256];
	{
        unsigned int iteration = 0xFF << shiftR;
        unsigned int *cp = index;
        for (int i = 255; i >=0; --i, ++cp)
                *cp = 0;
		for(int i=0;i<n;i++){
			u32 mask = (src[i] & iteration) >> shiftR;
			index[mask] ++;
		}

		unsigned int preSum = 0;
		for(int i=0;i<256;i++){
			unsigned int tmp = index[i];
			index[i] = preSum;
			preSum += tmp;
		}


		for(int i=0;i<n;i++){
			u32 curEle = src[i];
			u32 mask = (curEle & iteration) >> shiftR;
			dst[ index[mask] ] = curEle;
			index[mask] ++;
		}
	}
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  binSort_byteXX
 *  Description:
 *  	  Input:  
 *       Output:
 *      Example:  binSort_byteXX
 * =====================================================================================
 */
void binSort_byteXX(u32 *a, unsigned int n)
{
     u32 *tmpbuf = buf;
     binSort_byte_one_radix(a, tmpbuf, n, 0);
     binSort_byte_one_radix(tmpbuf, a, n, 8);
     binSort_byte_one_radix(a, tmpbuf, n, 16);
     binSort_byte_one_radix(tmpbuf, a, n, 24);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  binSort_byte
 *  Description:
 *  	  Input:  
 *       Output:
 *      Example:  binSort_byte
 * =====================================================================================
 */
void binSort_byte(u32 *a,  unsigned int n)
{
	unsigned 	int iteration = 1;
	u32* src = a;
	u32* dst = buf;
	__ALIGN__ unsigned int index[256];
	int shiftR = 0;
	for(iteration = 0xFF; iteration !=0; iteration = iteration << 8, shiftR +=8)
	{
        unsigned int *cp = index;
        for (int i = 255; i >=0; --i, ++cp)
                *cp = 0;
		for(int i=0;i<n;i++){
			u32 mask = (src[i] & iteration) >> shiftR;
			index[mask] ++;
		}

		unsigned int preSum = 0;
		for(int i=0;i<256;i++){
			unsigned int tmp = index[i];
			index[i] = preSum;
			preSum += tmp;
		}


		for(int i=0;i<n;i++){
			u32 curEle = src[i];
			u32 mask = (curEle & iteration) >> shiftR;
			dst[ index[mask] ] = curEle;
			index[mask] ++;
		}

		swapPtr(src, dst);
	}
	if(a != src)
		copyBack(a, src, n);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  binSort_byte4
 *  Description:
 *  	  Input:  
 *       Output:
 *      Example:  binSort_byte4
 * =====================================================================================
 */
void binSortV(u32 *a,  unsigned int n)
{
	unsigned 	int iteration ;
	u32* src = a;
	u32* dst = buf;
	__ALIGN__ int index[256*4];
	int shiftR = 0;
	for(int i=0;i<256*4;i++) index[i] =0;
	for(int i=0;i<n;i++){
		__ALIGN__ 	u32 mask[4];
		u32 curEle = src[i];
		mask[0] = (curEle & 0xFF) ;
		mask[1] = (curEle & 0xFF00) >> 8 ;
		mask[2] = (curEle & 0xFF0000) >> 16;
		mask[3] = (curEle & 0xFF000000) >> 24;
		index[mask[0]*4 + 0] ++;
		index[mask[1]*4 + 1] ++;
		index[mask[2]*4 + 2] ++;
		index[mask[3]*4 + 3] ++;
	}

	unsigned int preSum[4] = {0,0,0,0};
	for(int i=0;i<256;i++){
		unsigned int tmp[4]  = {index[i*4], index[i*4+1], index[i*4+2], index[i*4+3]};
		index[i*4 + 0] =preSum[0];
		index[i*4 + 1] =preSum[1];
		index[i*4 + 2] =preSum[2];
		index[i*4 + 3] =preSum[3];
		preSum[0]+= tmp[0];
		preSum[1]+= tmp[1];
		preSum[2]+= tmp[2];
		preSum[3]+= tmp[3];
	}

	int step;
	for(iteration = 0xFF, step = 0; iteration !=0; iteration = iteration << 8, shiftR +=8, step++)
	{
		for(int i=0;i<n;i++){
			u32 curEle = src[i];
			u32 mask = (curEle & iteration) >> shiftR;
			dst[ index[mask*4 + step] ] = curEle;
			index[mask*4 + step] ++;
		}
		swapPtr(src, dst);
	}
	if(a != src)
		copyBack(a, src, n);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  binSort_byteSSE
 *  Description:
 *  	  Input:  
 *       Output:
 *      Example:  binSort_byteSSE
 * =====================================================================================
 */
void binSortSSE(u32 *a,  unsigned int n)
{
	unsigned 	int iteration ;
	u32* src = a;
	u32* dst = buf;
	__ALIGN__ int index[256*4];
	int shiftR = 0;
	__m128i FFv = _mm_set1_epi32( 0xFF);
	__m128i FF00v = _mm_set1_epi32( 0xFF00);
	__m128i FF0000v = _mm_set1_epi32( 0xFF0000);
	__m128i FF000000v = _mm_set1_epi32( 0xFF000000);
	for(int i=0;i<256*4;i++) index[i] =0;
	for(int i=0;i<n;i+=4){
		__m128i elev;
		__m128i maskv;
		__ALIGN__ u32 mask[4];
		elev = _mm_load_si128((__m128i*) &a[i]); 
		maskv = _mm_and_si128( elev, FFv);
		_mm_store_si128((__m128i*)mask, maskv);
		index[mask[0]*4 + 0] ++;
		index[mask[1]*4 + 0] ++;
		index[mask[2]*4 + 0] ++;
		index[mask[3]*4 + 0] ++;
		maskv = _mm_and_si128( elev, FF00v);
		maskv = _mm_srli_epi32(maskv, 8);
		_mm_store_si128((__m128i*)mask, maskv);
		index[mask[0]*4 + 1] ++;
		index[mask[1]*4 + 1] ++;
		index[mask[2]*4 + 1] ++;
		index[mask[3]*4 + 1] ++;
		maskv = _mm_and_si128( elev, FF0000v);
		maskv = _mm_srli_epi32(maskv, 16);
		_mm_store_si128((__m128i*)mask, maskv);
		index[mask[0]*4 + 2] ++;
		index[mask[1]*4 + 2] ++;
		index[mask[2]*4 + 2] ++;
		index[mask[3]*4 + 2] ++;
		maskv = _mm_and_si128( elev, FF000000v);
		maskv = _mm_srli_epi32(maskv, 24);
		_mm_store_si128((__m128i*)mask, maskv);
		index[mask[0]*4 + 3] ++;
		index[mask[1]*4 + 3] ++;
		index[mask[2]*4 + 3] ++;
		index[mask[3]*4 + 3] ++;
	}

	__m128i lastv, psumv;
	lastv =  _mm_load_si128((__m128i*) &index[0*4]);
	psumv = _mm_xor_si128(psumv, psumv );
	_mm_store_si128((__m128i*) &index[0], psumv);
	
	for(int i=1;i<256;i++){
		__m128i tmpv = _mm_load_si128((__m128i*) &index[i*4]);
		psumv = _mm_add_epi32(psumv, lastv);
		_mm_store_si128((__m128i*) &index[i*4], psumv);
		lastv = tmpv;
	}

	int step;
	for(iteration = 0xFF, step = 0; iteration !=0; iteration = iteration << 8, shiftR +=8, step++)
	{
		for(int i=0;i<n;i++){
			u32 curEle = src[i];
			u32 mask = (curEle & iteration) >> shiftR;
			dst[ index[mask*4 + step] ] = curEle;
			index[mask*4 + step] ++;
		}
		swapPtr(src, dst);
	}
	if(a != src)
		copyBack(a, src, n);
}




void binSort(u32 *a,  unsigned int n)
{
	binSort_byte(a, n);
}

/* ******************************************************************************************** */
template<typename T>
static void binSort_byte_one_radix(T *src, T* dst,  unsigned int n, unsigned int mask, int shiftR)
{
	__ALIGN__ unsigned int index[256];
	{
        unsigned int *cp = index;
        for (int i = 255; i >=0; --i, ++cp)
                *cp = 0;
		for(int i=0;i<n;i++){
			u32 maskRadix = (src[i] & mask) >> shiftR;
			index[maskRadix ] ++;
		}

		unsigned int preSum = 0;
		for(int i=0;i<256;i++){
			unsigned int tmp = index[i];
			index[i] = preSum;
			preSum += tmp;
		}


		for(int i=0;i<n;i++){
			T curEle = src[i];
			u32 maskRadix  = (curEle & mask) >> shiftR;
			dst[ index[maskRadix ] ] = curEle;
			index[maskRadix ] ++;
		}
	}
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  splitPosNeg
 *  Description:  The float may be + or -, the binSort does not use the sign, 
 *                So after binSort, should sort again by the sign.
 *  	  Input:  
 *       Output:
 *      Example:  splitPosNeg
 * =====================================================================================
 */
template<typename T>
static void splitPosNeg(T* src, T *dst, int n)
{
    T* pstart = dst;
    T* pend = pstart + n -1;
    for(int i=n-1;i>=0;i--){
        if(src[i] > 0){
            *pend = src[i];
            pend --;
        }else{
            *pstart = src[i];
            pstart ++;
        }
    }
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  binSort_byte
 *  Description:  Sort the float 1-8-23
 *  	  Input:  
 *       Output:
 *      Example:  binSort_byte
 * =====================================================================================
 */
void binSort_byte(float *a, unsigned int n)
{
     float *tmpbuf = (float*)buf;
     float *tmpbuf2 = (float*)buf + n;
     binSort_byte_one_radix((u32*)a, (u32*)tmpbuf, n, 0,           0);
     binSort_byte_one_radix((u32*)tmpbuf, (u32*)a, n, (0x7F<<8),   8);
     binSort_byte_one_radix((u32*)a, (u32*)tmpbuf, n, (0x7F<<16), 16);
     binSort_byte_one_radix((u32*)tmpbuf, (u32*)tmpbuf2, n, (0xFF<<23), 23);
     splitPosNeg((int*)tmpbuf2, (int*)a, n);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  binSort_byte
 *  Description:  Sort the double 1-11-52
 *  	  Input:  
 *       Output:
 *      Example:  binSort_byte
 * =====================================================================================
 */
void binSort_byte(double*a, unsigned int n)
{

}
