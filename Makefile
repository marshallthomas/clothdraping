## Compiler
CC=g++
## Linker
LD=$(CC)
## Flags
CPPFLAGS = -Wall -g -DLINUX
LFLAGS = -lglut -L/usr/lib -L/usr/X11R6/lib -lXi -lXmu -lGL -lGLU -lm

TARGETS = $(PROGFILES:.cpp=)

PROGFILES = \
        assn5.cpp \
        $(NULL)

targets default: $(TARGETS)

$(PROGFILES:.cpp=): assn5.o 
	$(CC) -o assn5 assn5.o assn5lib.h assn5structs.h assn5globals.h ${LFLAGS}

depend :
	makedepend ${PROGFILES}
clean :
	rm assn5 assn5.o
# DO NOT DELETE
