# Quick and dirty (does not handle changes in h-file)
SRCS=main.cpp UIController.cpp ManualController.cpp AutomaticController.cpp Cradle.cpp Mobile.cpp ZigBeeIF_out.cpp ZigBeeIF_in.cpp Settings.hpp SettingsController.cpp MeasurementsController.cpp
OBJS=$(SRCS:.cpp=.o)
BASEPATH=..
# Determine whether this is a debug build or not

ifndef
TARGET=host
endif

# Her ændres compileren og filnavnet alt efter, hvad man vælger. 

ifeq (${TARGET},host)
CXX=g++
MAINPROGRAM=main.host
endif

ifeq (${TARGET},target)
CXX=arm-angstrom-linux-gnueabi-g++
MAINPROGRAM=main.target
endif

ifdef DEBUG
CXXFLAGS=-ggdb -O0
LIBPATH=$(BASEPATH)/lib/${TARGET}/debug
else
CXXFLAGS=-O2
LIBPATH=$(BASEPATH)/lib/${TARGET}/release
endif

# Setup the CFLAGS to ensure that the relevant warnings, includes and defines.
CXXFLAGS+=-Wall -D_REENTRANT -DOS_LINUX -I$(BASEPATH)/inc

#%.o : %cpp
#	g++ $(CXXFLAGS) -c -o $@ $^
# Then again, note how the flags are NOT part of the linking process

# Compilervariablen ${CXX} indsættes naturligvis også.

main: $(OBJS)
	${CXX} -o ${MAINPROGRAM} $(OBJS)  -L$(LIBPATH) -lOSApi -lrt -lpthread

all: main

clean:$(OBJS)
	rm -f *.o ${MAINPROGRAM}