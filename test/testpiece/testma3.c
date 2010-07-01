#define compute(a, b) { int ia =a; int ib = b; int ic= (ia *ib) + (ia<<1); ic;}

int main()
{
	int a, b, c,d;
	int ea, eb;
	a = 2;
	b = 4;
	c = 0;
//	c = compute(a, b);
c = (ea=a, eb=b,d=ea+eb,d);
printf("%d %d\n", c,d);
}
