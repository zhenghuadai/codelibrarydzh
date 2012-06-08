/*
 * =====================================================================================
 *
 *       Filename:  SOA.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/30/2012 11:54:06 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <rdtsc.h>
#include <mm_malloc.h>

struct Complexshadow
{
        Complexshadow(int& r, int& g):r(r),i(g){}
        int& r;
        int& i;
};


template<class T>
class SOA
{
};

template<class Shadow, class T1, class T2 = void, class T3 = void ,
class T4 = void, class T5 = void, class T6 = void, 
class T7 = void, class T8 = void, class T9 = void, 
class T10= void, class T11= void, class T12= void
>
class AX
{

};

template<class Shadow, class T1, class T2 >
class SOA<AX<Shadow, T1, T2> >
{
    public:
        typedef T1 aligned_t1 __attribute__((aligned(16)));
        typedef T2 aligned_t2 __attribute__((aligned(16)));
    public:
        SOA(int n):m_size(n){
            r = (aligned_t1*)_mm_malloc(n*sizeof(T1), 64);
            g = (aligned_t2*)_mm_malloc(n*sizeof(T2), 64);
        }
        ~SOA(){
            if(r) _mm_free(r);
            if(g) _mm_free(g);
        }
        Shadow operator [] ( size_t i){
            return Shadow(r[i],g[i]);
        }
    public:
        size_t size(){ return m_size;}
    private:
        size_t m_size;
        aligned_t1* r ;
        aligned_t2* g ;
};


template<class Shadow, class T1, class T2, class T3>
class SOA<AX< Shadow, T1, T2, T3> >
{
    public:
        typedef T1 aligned_t1 __attribute__((aligned(16)));
        typedef T2 aligned_t2 __attribute__((aligned(16)));
        typedef T3 aligned_t3 __attribute__((aligned(16)));
    public:
        SOA(int n):m_size(n){
            r = (aligned_t1*)_mm_malloc(n*sizeof(T1), 64);
            g = (aligned_t2*)_mm_malloc(n*sizeof(T2), 64);
            b = (aligned_t3*)_mm_malloc(n*sizeof(T3), 64);
        }
        ~SOA(){
            if(r) _mm_free(r);
            if(g) _mm_free(g);
            if(b) _mm_free(b);
        }
        Shadow operator [] ( size_t i){
            return Shadow(r[i],g[i],b[i]);
        }
    public:
        size_t size(){ return m_size;}
    private:
        size_t m_size;
        aligned_t1* r ;
        aligned_t2* g ;
        aligned_t3* b ;
};

