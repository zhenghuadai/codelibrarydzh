all:testThreadWrapper.exe

%.o:%.c
	$(CC) -c $< -I../include 
%.exe:%.o
	$(CC) -o $@ $< -lpthread
