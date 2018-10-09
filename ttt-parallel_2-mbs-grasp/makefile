########### COMPILADORES E PARAMETROS
#CCC           = g++-5
#CCC           = g++
CCC           = /opt/openmpi-2.1.1/bin/mpic++
CFLAGS        =  -Wall  -Wno-deprecated -Wno-write-strings -O3 #-ansi
DEBUG         =  -D DEBUG_ALL

# Fontes
DIRS    := . 
SOURCES := $(foreach dir, $(DIRS), $(wildcard $(dir)/*.cpp))
OBJS    := $(patsubst %.cpp, %.o, $(SOURCES))

########## BIBLIOTECAS

# Matematica
LIBSM          =  -lm -lrt

LIBS = $(LIBSM) 

#### COPILAR

all: dmer

dmer: ${OBJS}
	${CCC} ${CFLAGS}  $(DEBUG) -o $@ $(OBJS) $(LIBS)

.cpp.o:
	$(CCC) $(CFLAGS) $(DEBUG) $< -c -o $@


#### LIMPEZA GOLS

clean:
	-rm -f ${OBJS} dmer
