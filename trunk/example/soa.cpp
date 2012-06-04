/*
 * =====================================================================================
 *
 *       Filename:  SOA.cpp
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


struct RGB
{
        int r;
        int g;
        int b;
};

struct RGBshadow
{
        RGBshadow(int& r, int& g, int& b):r(r),g(g),b(b){}
        int& r;
        int& g;
        int& b;
};

template<class Shadow, typename T1, typename T2, typename T3>
class SOA
{
    public:
        typedef T1 aligned_t1 __attribute__((aligned(16)));
        typedef T2 aligned_t2 __attribute__((aligned(16)));
        typedef T3 aligned_t3 __attribute__((aligned(16)));
    public:
        SOA(int n){
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
    private:
        aligned_t1* r ;
        aligned_t2* g ;
        aligned_t3* b ;
};

#define SIZE 65536
int main()
{
    RGB* rgb = new RGB[SIZE]; 
    SOA<RGBshadow, int, int,int> soa(SIZE); 
    int i =0;
    for(i=0;i<SIZE;i++){
        rgb[i].r = 3*i;
        rgb[i].g = 3*i + 1;
        rgb[i].b = 3*i + 2;
    }

    for(i=0;i<SIZE;i++){
        soa[i].r = 3*i;
        soa[i].g = 3*i + 1;
        soa[i].b = 3*i + 2;
    }
    for(int j=0; j<4;j++){
        pdtime(0);
        for(i=0;i<SIZE;i++){
            rgb[i].b=rgb[i].r + rgb[i].g;
        }
        pdtime(1);
        pdtime(0);
        for(i=0;i<SIZE;i++){
            soa[i].b=soa[i].r + soa[i].g;
        }
        pdtime(1);
        printf("loop %d\n", j);
    }
    delete rgb;
}
