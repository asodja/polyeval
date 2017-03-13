CC=gcc
CFLAGS=-O3 -std=c99
LIBS=-lm

all: SingleSparseReal clean

SingleSparseReal: common.o SingleSparseReal.o
	$(CC) $(CFLAGS) $(LIBS) -o $@ $^

common.o: common.c common.h
	$(CC) $(CFLAGS) -c common.c $(LIBS)

clean: 
	rm -f *.o *.~

