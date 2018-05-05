CC = gcc
CFLAGS = -std=c99 -g -Wall -ansi
DEPS = auxiliaryFunctions.h
OBJ = main.o auxiliaryFunctions.o
SRC = main.c auxiliaryFunctions.c

all: test clean

test: $(OBJ) 
	$(CC) $(CFLAGS) -o $@ $+

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o
