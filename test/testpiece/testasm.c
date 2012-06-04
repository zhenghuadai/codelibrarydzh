#include <stdio.h>

#define Str(x) #x
#define Str2(x) Str(x)
#define ecx_ c

#define inRistrict(x) = ## x
#define inRistrict2(x) inRistrict(x)
#define Abbbbb(x) x##_ 
#define masm__m2E(x, e, m)       __asm__(" ":"="Str2(Abbbbb(e))(m)::);
typedef size_t x86_reg;
void testasm()
{
    int a=1,b=2,c=3;
    unsigned char *src = 0, *dst = 0;
    __asm__(
           // 	"movl %1, %%eax \n"
            //	"addl $1, %%eax\n"
            //:"+a"(a):"c"(c)
            " "
            :"=a"(b) 
            :
         );
    printf("a=%d\n", a);
    //masm__m2E(mov, ecx, a);
    __asm__ (" ":"=c"(a):);


    __asm__(
            "add %0, %2 \n"
            : "+a"(src), "+c"(dst)\ 
            :"S"((x86_reg)a), "r"((x86_reg)b)
           );
}

int main()
{
    testasm();
}
