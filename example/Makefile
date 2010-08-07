all:testThreadWrapper.exe
CC=gcc -g -O0
CXX=g++ -g -O0
GLUT = -lglut
XLIBS = $(GLUT) -lGLU -lGL -lXext -lX11 -lm #-lXmu 
%.o:%.c
	$(CC) -c $< -I../include ${XLIBS}
%.exe:%.o
	$(CC) -o $@ $< -lpthread ${XLIBS}
%.xexe:%.cpp
	$(CXX) -o $@ $< -lpthread ${XLIBS}
%:%.cpp	
	$(CXX) -o $@ $< -lpthread ${XLIBS}
clean:
	rm *.o *.exe
testThreadWrapper.o: testThreadWrapper.c ../include/threadWrapper.h ../include/threadPool.h
