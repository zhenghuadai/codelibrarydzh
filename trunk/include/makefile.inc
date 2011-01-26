MPICC=mpic++ #/usr/bin/mpic++
CC=gcc
CXX=g++
LD=$(if $(compiler), $(compiler), gcc)
LD++=$(if $(compiler), $(compiler), g++)
#LD++?=g++
ROOT_PATH=${HOME}
INC_PATH=-I${ROOT_PATH}/include 
LIB_PATH=-L${ROOT_PATH}/lib
LIBS+=$(foreach i, ${ext_lib},-l$(i))
INC_PATH+=$(foreach i, ${ext_inc},-I$(i))
LIB_PATH+=$(foreach i, ${ext_libpath},-L$(i))
XLIBS= -lglut -lGLU -lGL -lXext -lX11 -lm #-lXmu 

ifeq ($(debug),yes)
CFLAGS:=-g 
else
ifeq ($(debug),go2)
CFLAGS:=-g -O2
else
CFLAGS:=-O2
endif
endif

define linktemplate
	${LD} ${CFLAGS}  ${LIB_PATH} ${LIBS} -o $@ $^ 
endef    
LINK=$(call linktemplate)
define linktemplate++
	${LD++} ${CFLAGS}  ${LIB_PATH} ${LIBS} -o $@ $^ 
endef    
LINK++=$(call linktemplate++)

all: ${TARGET}

all: ${TARGET}
%.exe:%.c.o  
	${LINK} 
    #${LD} ${CFLAGS} -I${INC_PATH} ${LIB_PATH} ${LIBS} -o $@ $^ 
%.exe:%.cpp.o  
	${LINK++} 
    #${LD} ${CFLAGS} -I${INC_PATH} ${LIB_PATH} ${LIBS} -o $@ $^ 
%.c.o %.o:%.c
	${CC} ${CFLAGS}  ${INC_PATH} -c $< -o $@ -MMD 
%.cpp.o %.o:%.cpp
	${CXX} ${CFLAGS}  ${INC_PATH} -c $< -o $@ -MMD 
%.xexe:%.cpp
	$(CXX) -o $@ $< -lpthread ${XLIBS}
depfile=$(wildcard *.d)	
-include ${depfile}
clean:
	rm -f *.o *.exe *.d
	
