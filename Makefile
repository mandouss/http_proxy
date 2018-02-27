CC=g++
CFLAGS=-std=c++11 -pedantic -Wall -ggdb3 -Werror -pthread
SOURCES=socket.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=socket

all: $(EXECUTABLE)

$(EXECUTABLE): socket.o 
	$(CC) $(CFLAGS) socket.o -o $(EXECUTABLE)

socket.o: socket.cpp socket.h threadcontrol.h
	$(CC) $(CFLAGS) -c socket.cpp

clean:
	rm -f *~ *.o $EXECUTABLE
