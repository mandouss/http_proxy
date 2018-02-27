CC=g++
CFLAGS=-std=c++11 -pedantic -Wall -ggdb3 -Werror -pthread
SOURCES=socket.cpp 
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=socket test

all: socket test

socket: socket.o 
	$(CC) $(CFLAGS) -o $@ socket.o
test: test.o
	gcc -std=gnu99 -pedantic -Wall -ggdb3 -Werror -o $@ test.o

socket.o: socket.cpp socket.h threadcontrol.h
	$(CC) $(CFLAGS) -c socket.cpp

test.o: test.c
	gcc -std=gnu99 -pedantic -Wall -ggdb3 -Werror -c test.c

clean:
	rm -f *~ *.o socket test
