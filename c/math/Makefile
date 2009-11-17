ifeq "$(debug)" "yes"
FLAG= -g
else 
FLAG= -O2
endif
CXX=g++ 
arch=$(shell uname -m)
#the cpu MHz will change when running 
#get the frequency
scaling_max_freq_fn=/sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq

ifeq ($(scaling_max_freq_fn), $(wildcard ${scaling_max_freq_fn}))
scaling_max_freq_exist=yes
coreFrequencyK=$(shell cat ${scaling_max_freq_fn})
#coreFrequencyM=$(shell expr ${coreFrequencyK} / 1000)
coreFrequencyM=$(shell echo "scale=1; ${coreFrequencyK} / 1000.0" | bc -l )
FLAG+= -DFREQ=$(coreFrequencyM) 
else
scaling_max_freq_exist=no
coreFrequencyM=$(shell grep MHz /proc/cpuinfo | uniq | sed "s/[\\t\\n: a-zA-Z]//g")
FLAG+= -DFREQ=$(coreFrequencyM)
endif

ifeq "$(arch)" "x86_64"
FLAG+= -DX64
else 
FLAG+= -m32 
endif

FLAG+= -DUSE_SSE2 

ICCFLAG=${FLAG}
GCCFLAG=${FLAG} -msse2 -DREF_FREQ_MHZ=$(coreFrequencyM) 

all : test1 
test1:test1.o sincosd.o sincosf.o	
	${CXX} ${GCCFLAG} -o $@ $^
test2:sse_mathfun_test.c sincosd.o sincosf.o	
	${CXX} ${GCCFLAG} -o $@ $^
%.o:%.cpp 
	${CXX} ${GCCFLAG} -c  -o $@ $<
%.o:%.c 
	${CXX} ${GCCFLAG} -c -o $@ $<
clean:
	rm -rf *.o *.s *.S
