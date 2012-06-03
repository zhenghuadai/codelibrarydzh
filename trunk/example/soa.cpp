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

class RGB
{
    public:
        int r;
        int g;
        int b;
};

class RGBref
{
    public:
        RGBref(int& r, int& g, int& b):r(r),g(g),b(b){}
    public:
        int& r;
        int& g;
        int& b;
};


class SOA
{
    public:
        SOA(int n){
            r = new int[n];
            g = new int[n];
            b = new int[n];
        }
        ~SOA(){
            if(r) delete r;
            if(g) delete g;
            if(b) delete b;
        }
        RGBref operator [] ( size_t i){
            return RGBref(r[i],g[i],b[i]);
        }
    private:
        int* r;
        int* g;
        int* b;
};

#define SIZE 65536
int main()
{
    RGB* rgb = new RGB[SIZE]; 
    SOA soa(SIZE); 
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
