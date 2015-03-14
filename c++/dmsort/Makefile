CXX = g++
CC  = gcc
OBJDIR = obj
all: testint 
ifeq "${debug}" "yes"
FLAG = -g -O0 -msse2 #-xP -ipo -guide #-D__USE_GNU -DUSE_setaffinity_ 
else
ifeq "${debug}" "go2"
FLAG = -g -O2 -msse2 #-xP -ipo -guide #-D__USE_GNU -DUSE_setaffinity_ 
else
FLAG = -O3 -msse2 #-xP -ipo -guide #-D__USE_GNU -DUSE_setaffinity_ 
endif
endif
CXXFLAG = ${FLAG}
CFLAG = ${FLAG}
COMMONPATH = ../../common
CXXFILES = 
CFILES = 
OBJS =  $(patsubst %.cpp,$(OBJDIR)/%.o,$(notdir $(CXXFILES)))
OBJS +=  $(patsubst %.c,$(OBJDIR)/%.o,$(notdir $(CFILES)))
INCLUDES += -I. -I${COMMONPATH}/include -Ialgorithms/ 
LIB = -lpthread   
CXXFILESINT= testint.cpp algorithms/binsort.cpp  algorithms/quick.cpp algorithms/quick_simple.cpp

sort:${OBJS}
	${CXX} -o $@ ${CXXFLAG} ${CXXFILES}  ${LIB}
sortSSEMerge:${OBJS}
	${CXX} -o $@ ${CXXFLAG}  ${CXXFILES} ${LIB}
sortomp:${OBJS}
	${CXX} -o $@ $^ ${LIB}
testint: ${CXXFILESINT}	
	${CXX} -o $@ ${CXXFLAG} ${INCLUDES} ${CXXFILESINT} ${LIB}
testfloat: testfloat.cpp algorithms/binsort.cpp algorithms/quick.cpp 
	g++ -o $@ ${CXXFLAG} ${INCLUDES} -msse2  $^  ${LIB}

$(OBJDIR)/%.o:%.cpp
	${CXX} -o $@ -c ${CXXFLAG} ${INCLUDES} $^
$(OBJDIR)/%.o:%.c
	${CC} -o $@ -c ${CFLAG} ${INCLUDES}  $^
makedirectories:
	@mkdir  -p ${OBJDIR}
clean:
	rm -f sort sortomp sortSSEMerge ${OBJDIR}/*.o testint

