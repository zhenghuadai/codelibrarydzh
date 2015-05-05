MPICC=mpic++ #/usr/bin/mpic++
CC=$(if $(compiler), $(compiler), gcc)
CXX=$(if $(compiler), $(compiler), g++)
LD=$(if $(compiler), $(compiler), gcc)
LD++ =$(if $(compiler), $(compiler), g++)
LEX++ :=flex
YACC++ :=bison
LEX=flex
YACC=bison

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
OBJ_DIR =.debug/
else
ifeq ($(debug),go2)
CFLAGS:=-g -O2
OBJ_DIR =i.debug/
else
CFLAGS:=-O2
OBJ_DIR =.release/
endif
endif

CPPFLAGS:=${CFLAGS} $(ext_cflags)

$(shell mkdir -p $(OBJ_DIR))
##############define template###########################################
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

#define compiletemplate++
#	@test -x ${dir $@} || mkdir -p ${dir $@} 
#	${CXX} ${CFLAGS}  ${INC_PATH} -c $< -o $@ -MMD ;\
#endef    
define compiletemplate++
	@test -x ${dir $@} || mkdir -p ${dir $@} 
	ch2=`head -c 2 $<`; if [ "$$ch2" != '#!' ]; then \
	${CXX} ${CPPFLAGS}  ${INC_PATH} -c $< -o $@ -MMD ;\
	else \
	tail --lines=+2 $< > ${dir $@}/$<.cpp;\
	${CXX} ${CPPFLAGS}  ${INC_PATH} -c ${dir $@}/$<.cpp -o $@ -MMD ;\
	fi;
endef    
COMPILE++ =$(call compiletemplate++)


define getobjs
$(foreach i, $1, $(OBJ_DIR)$(if $(filter ../%,$i),$(subst ..,UP,$i),$i).o)
endef
##############define template###########################################

DEFAULT_OBJS=$(call getobjs, $(SOURCEFILE))
DEFAULT_LINK=$(if $(filter %.cpp, $(SOURCEFILE)),${LINK++}, ${LINK})

TARGET?=${EXECUTABLE}

all: ${TARGET}
${EXECUTABLE}:${DEFAULT_OBJS} 
	${DEFAULT_LINK} 
%.exe:${OBJ_DIR}%.c.o  
	${LINK} 
%.exe:${OBJ_DIR}%.cpp.o  
	${LINK++} 

%.c.o %.o ${OBJ_DIR}%.c.o ${OBJ_DIR}%.o :%.c
	${COMPILE}
${OBJ_DIR}%.cpp.o ${OBJ_DIR}%.o %.cpp.o %.o :%.cpp
	${COMPILE++}

${OBJ_DIR}UP/%.cpp.o:$(subst UP,..,UP/%.cpp) 
	${COMPILE++}

%.xexe:%.cpp
	$(CXX) -o $@ $< -lpthread ${XLIBS}

    
depfile=$(wildcard ${OBJ_DIR}*.d)	
-include ${depfile}
clean:
	rm -f *.o *.exe *.d ${CLEAN_OBJ}
	rm  -rf .release .debug
