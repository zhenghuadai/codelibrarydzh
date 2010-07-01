#include <stdio.h>

#define Str(x) #x
#define Str2(x) Str(x)
#define ecx_ c

#define inRistrict(x) = ## x
#define inRistrict2(x) inRistrict(x)
#define Abbbbb(x) x##_ 
#define masm__m2E(x, e, m)       __asm__(" ":"="Str2(Abbbbb(e))(m)::);

int main()
{
	int a=1,b=2,c=3;
	__asm(
//	"movl %1, %%eax \n"
//	"addl $1, %%eax\n"
	//:"+a"(a):"c"(c)
	" "
	:"=""a"(b) ::
	);
	printf("a=%d\n", a);
//masm__m2E(mov, ecx, a);
__asm__ (" ":"=c"(a):);
}
