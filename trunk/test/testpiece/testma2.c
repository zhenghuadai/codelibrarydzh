#define addr(x) [x]
#define q_addr(x) mmword ptr [x]
#define qaddr(x) mmword ptr [x]
#define nasm(op, op1, op2) op op1, op2
#define q_prefix mmword ptr
#define q_ptr(x) mmword ptr [x]
#define xmmove(op, op1, op2, size) nasm(op ##size, size##addr(ecx), op2)

xmmove(mov, xmm1, addr(ecx), q)
xmmove(mov, xmm1, addr(ecx), )
