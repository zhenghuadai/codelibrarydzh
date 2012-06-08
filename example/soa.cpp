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
#include <soa.hpp>

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

template<class T>
void test(T& rgb, size_t SIZE)
{
    int i;
     for(i=0;i<SIZE;i++){
        rgb[i].r = 3*i;
        rgb[i].g = 3*i + 1;
        rgb[i].b = 3*i + 2;
    }

        pdtime(0);
    for(i=0;i<SIZE;i++){
        rgb[i].b=rgb[i].r + rgb[i].g;
    }
        pdtime(1);

}
#define SIZE 65536
int main()
{
    RGB* rgb = new RGB[SIZE]; 
    SOA<AX<RGBshadow, int, int,int> > soa(SIZE); 
    SOA<AX<Complexshadow, int, int> > soc(SIZE); 
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
    test(rgb, SIZE);
    test(soa, SIZE);
    delete rgb;
}
