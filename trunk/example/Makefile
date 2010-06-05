all:testThreadWrapper.exe

%.o:%.c
	$(CC) -c $< -I../include 
%.exe:%.o
	$(CC) -o $@ $< -lpthread

testThreadWrapper.o: testThreadWrapper.c ../include/threadWrapper.h ../include/threadPool.h
