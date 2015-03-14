CC= g++ -g 
cache:cachemain.o libcachesim.a
	${CC} -o $@ $^
	#${CC} -o $@ -WI,-Bstatic cachesim -L./ $<
	
cached:cachemain.o
	${CC} -o $@ -lcachesim -L./ $^
lib:cachesimlib
libcachesim.a:liba
liba:cacheclass.o
	ar cqs libcachesim.a $<
	
cachesimlib:cacheclass.o
	gcc -shared -Wl,-soname,libcachesim.so.1 -o libcachesim.so.1 $<
#cachesimlib.o:cacheclass.cpp cacheclass.h
%.o:%.cpp
	${CC} -c -fPIC $<
clean:
	rm -f libcachesim.so.1
	rm -f cache
	rm -f *.o *.a
#cacheclass.o:	cacheclass.h
