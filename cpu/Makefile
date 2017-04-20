CC=gcc
CFLAGS=-O3 -std=c99
LIBS=-lm

all: SingleSparseReal SingleSparseComplex MultiSparseReal MultiSparseComplex MultiDenseReal MultiDenseComplex clean

SingleSparseReal: common.o SingleSparseReal.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

SingleSparseComplex: common.o SingleSparseComplex.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

MultiSparseReal: common.o MultiSparseReal.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

MultiSparseComplex: common.o MultiSparseComplex.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

MultiDenseReal: common.o MultiDenseReal.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

MultiDenseComplex: common.o MultiDenseComplex.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

common.o: common.c common.h
	$(CC) $(CFLAGS) -c common.c $(LIBS)

clean: 
	rm -f *.o *.~

