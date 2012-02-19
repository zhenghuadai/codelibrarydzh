#include <stdio.h>

unsigned long long getrdtsc(){
	asm("rdtsc");
}
static void __ticket_spin_lock( int lock)
{
	short inc = 0x0100;

	asm volatile (
			"xaddw %w0, %1\n"
			"1:\t"
			"cmpb %h0, %b0\n\t"
			"je 2f\n\t"
			"rep ; nop\n\t"
			"movb %1, %b0\n\t"
			/*  don't need lfence here, because loads are in-order */
			"jmp 1b\n"
			"2:"
			: "+Q" (inc), "+m" (lock)
			:
			: "memory", "cc", "%eax");
}
int abc;
void testasm1()
{
    __asm__(
            "mov %0, %%ecx\n"
            :
            :"m"(abc)
           );
}

int main(){
    unsigned long long a,b;
    int ia=0;
    a = getrdtsc();
    b = getrdtsc();
    //	asm("addl $1, %a0"::"r"(ia));
    //asm("addl $1, %w0"::"r"(ia));
    //asm("addb $1, %a0"::"r"(ia));
    //asm("addb $1, %b0"::"r"(ia));
    //asm("addl $1, %b1"::"r"(ia));
    //asm("addb $1, %h0"::"r"(ia));
    printf("%ld\n", b -a);
    //asm("addb $1, %b0"::"r"(ia));
}
