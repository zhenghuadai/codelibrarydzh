all:testThreadWrapper.exe
CC=gcc -g
%.o:%.c
	$(CC) -c $< -I../include 
%.exe:%.o
	$(CC) -o $@ $< -lpthread
clean:
	rm *.o *.exe
testThreadWrapper.o: testThreadWrapper.c ../include/threadWrapper.h ../include/threadPool.h
