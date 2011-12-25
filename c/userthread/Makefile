all:testg test ctxthread

testg: dmthread.c sigtimer.c test.c create.c
	gcc -g -O0 -o $@ $^ 
test: dmthread.c sigtimer.o test.c create.o
	gcc -g  -O3 -o $@ $^
create.o:create.c
	gcc -c -g -o $@ $^
dmthread.o:dmthread.c
	gcc -c -g -o $@ $^

ctxthread:ctxthread.c test.c	
	gcc -g  -O3 -o $@ $^

%.o:%.c
	gcc -c -O3  -o $@ $^
clean:
	rm -df *.o test testg ctxthread
dmthread.c:dmthread.h
sigtimer.c:dmthread.h
create.c:dmthread.h
