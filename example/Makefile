all:testThreadWrapper.exe
CC=gcc -g
CXX=g++ -g
GLUT = -lglut
XLIBS = $(GLUT) -lGLU -lGL -lXext -lX11 -lm #-lXmu 
%.o:%.c
	$(CC) -c $< -I../include 
%.exe:%.o
	$(CC) -o $@ $< -lpthread
%.xexe:%.cpp
	$(CXX) -o $@ $< -lpthread ${XLIBS}
clean:
	rm *.o *.exe
testThreadWrapper.o: testThreadWrapper.c ../include/threadWrapper.h ../include/threadPool.h
