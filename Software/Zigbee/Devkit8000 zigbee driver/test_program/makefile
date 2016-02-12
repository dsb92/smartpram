# Define sources and objects
SOURCES = test_program.cpp
OBJECTS = ${SOURCES:.cpp=.o}
DEPENDENCIES = ${SOURCES:.cpp=.d}
LIBRARY = -pthread
# Define the resulting executables name and command targets
EXECUTABLE = test_program.target
TARGETS = all clean help

# Define compiler options and flags, (blanks are ok).
CXX = arm-angstrom-linux-gnueabi-g++
CXXFLAGS = 


${EXECUTABLE}: ${DEPENDENCIES} ${OBJECTS}
	${CXX} ${LIBRARY} -o $@ ${OBJECTS}

%.d: %.cpp
	${CXX} -MT${@:.d=.o} -MM ${CXXFLAGS} $^ > $@

-include $(DEPENDENCIES)


# Runs all commands specified
all: ${EXECUTABLE}

# Cleanup routine
clean:
	rm ${EXECUTABLE} ${OBJECTS} ${DEPENDENCIES}

# Help routine, lists available targets
help:
	@echo ${TARGETS}

