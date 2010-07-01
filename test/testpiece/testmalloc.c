#include "stdio.h"

void test(size_t n)
{
    char* p;
    size_t * sp;
    int *ip;
    printf("sizeof(size_t):%d\n", sizeof(size_t));
    p = (char*)malloc(n);
    sp = (size_t*)p;
    ip = (int*)p;
    printf(" %d %d ---- %d\n",*(ip-2), (*(ip-1)) & (~7), n);
    printf(" %d %d ---- %d\n",*(sp-2), (*(sp-1)) & (~7), n);
    _msize(ip);
    free(p);
}

int main(int argc,char**argv)
{
    int n = 10;
    if(argc > 1)
        n= atoi(argv[1]);
    test(n);
}
