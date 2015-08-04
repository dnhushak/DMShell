#Core Audio Devices makefile
CXX = gcc
LDFLAGS = -Wall -pedantic -Wextra
CFLAGS = -O3 -g

#File Extensions
HEADER = .h
SOURCE = .c
BINARY = .o

#Directories
SRCEDIR = ./
DIRLIST = $(SRCEDIR)

#Final Executable Name
EXE = DNDShell

# Generate list of source headers with extensions
HEADERS = $(foreach DIR, $(DIRLIST), $(wildcard $(DIR)*$(HEADER)))
SOURCES = $(foreach DIR, $(DIRLIST), $(wildcard $(DIR)*$(SOURCE)))
OBJECTS = $(addsuffix $(BINARY), $(notdir $(basename $(SOURCES))))
INCLUDE = $(foreach DIR, $(DIRLIST),-I$(DIR))

all: $(EXE)

clean:
	rm -rf $(EXE) *.o
	
$(EXE): $(OBJECTS)
	$(CXX) $(CFLAGS) $(OBJECTS) -o $(EXE) $(LDFLAGS) $(PAFLAGS) $(PMFLAGS)

force: clean $(EXE)

%$(BINARY) : $(SRCEDIR)%$(SOURCE)
	$(CXX) $(CFLAGS) $(INCLUDE) -c $< $(LDFLAGS) -o $@
	
depend:
	gccmakedep -- $(LDFLAGS3) -- $(SOURCES) $(HEADERS)



#
#
##Compiler
#CC = gcc
#
##Build Path
#SRCPATH = ./
#
##File information
#EXE = shell
#HEADERS = $(SRCPATH)splitArgs.h $(SRCPATH)execCommand.h $(SRCPATH)processHistory.h
#SRCS = $(SRCPATH)shell.c $(SRCPATH)splitArgs.c $(SRCPATH)execCommand.c $(SRCPATH)processHistory.c
#OBJECTS = splitArgs.o shell.o execCommand.o processHistory.o
#
##Library flags
#LDFLAGS = -g -Wall
##C compiler flags
#CFLAGS = 
#
#shell: $(OBJECTS)
#	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXE) $(LDFLAGS)
#
#shell.o: $(SRC)shell.c $(HEADERS)
#	$(CC) $(CFLAGS) -c $(SRC)shell.c $(LDFLAGS)
#
#splitArgs.o: $(SRC)splitArgs.c $(HEADERS)
#	$(CC) $(CFLAGS) -c $(SRC)splitArgs.c $(LDFLAGS)
#
#execCommand.o: $(SRC)execCommand.c $(HEADERS)
#	$(CC) $(CFLAGS) -c $(SRC)execCommand.c $(LDFLAGS)
#	
#processHistory.o: $(SRC)processHistory.c $(HEADERS)
#	$(CC) $(CFLAGS) -c $(SRC)processHistory.c $(LDFLAGS)
#
#clean:
#	rm -rf $(EXE) *.o
#	
#depend:
#	gccmakedep -- $(LDFLAGS) -- $(SRCS)
