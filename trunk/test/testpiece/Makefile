flags= -O2 -g  -I../../include
%.exe:%.c
	gcc -o $@ -msse2 ${flags}  $<
%.exe:%.cpp
	g++ -o $@ -msse2 ${flags} $<
clean:
	rm -f *.exe *.o *.s *.S

