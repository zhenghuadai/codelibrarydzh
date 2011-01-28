MPICC=mpic++ #/usr/bin/mpic++
CC=gcc
CXX=g++
LD=$(if $(compiler), $(compiler), gcc)
LD++ =$(if $(compiler), $(compiler), g++)
#LD++?=g++
ROOT_PATH=${HOME}
INC_PATH=-I${ROOT_PATH}/include 
LIB_PATH=-L${ROOT_PATH}/lib
LIBS+=$(foreach i, ${ext_lib},-l$(i))
INC_PATH+=$(foreach i, ${ext_inc},-I$(i))
LIB_PATH+=$(foreach i, ${ext_libpath},-L$(i))
XLIBS= -lglut -lGLU -lGL -lXext -lX11 -lm #-lXmu 
CLEAN_OBJ+=${clean_obj}
ifeq ($(debug),yes)
CFLAGS:=-g 
OBJ_DIR =debug/
else
ifeq ($(debug),go2)
CFLAGS:=-g -O2
OBJ_DIR =debug/
else
CFLAGS:=-O2
OBJ_DIR =release/
endif
endif

$(shell mkdir -p $(OBJ_DIR))

define linktemplate
	${LD}   ${CFLAGS} ${INC_PATH} ${LIB_PATH} ${LIBS} -o ${OBJ_DIR}$@ $^ 
endef    
LINK=$(call linktemplate)
define linktemplate++
	${LD++} ${CFLAGS} ${INC_PATH} ${LIB_PATH} ${LIBS} -o ${OBJ_DIR}$@ $^ 
endef    
LINK++ =$(call linktemplate++)

define compiletemplate
	@test -x ${dir $@} || mkdir -p ${dir $@} 
	${CC} ${CFLAGS}  ${INC_PATH} -c $< -o $@ -MMD 
endef    
COMPILE=$(call compiletemplate)
define compiletemplate++
	@test -x ${dir $@} || mkdir -p ${dir $@} 
	${CXX} ${CFLAGS}  ${INC_PATH} -c $< -o $@ -MMD 
endef    
COMPILE++ =$(call compiletemplate++)


define getobjs
$(foreach i, $1, $(OBJ_DIR)$i.o)
endef

all: ${TARGET}

all: ${TARGET}
%.exe:${OBJ_DIR}%.c.o  
	${LINK} 
%.exe:${OBJ_DIR}%.cpp.o  
	${LINK++} 

%.c.o %.o ${OBJ_DIR}%.c.o ${OBJ_DIR}%.o :%.c
	${COMPILE}
%.cpp.o %.o ${OBJ_DIR}%.cpp.o ${OBJ_DIR}%.o:%.cpp
	${COMPILE++}

%.xexe:%.cpp
	$(CXX) -o $@ $< -lpthread ${XLIBS}
depfile=$(wildcard *.d)	
-include ${depfile}
clean:
	rm -f *.o *.exe *.d ${CLEAN_OBJ}
	rm  -rf release debug
