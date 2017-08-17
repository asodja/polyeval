CC=gcc
CFLAGS=-O3 -std=c99
LIBS=-lm

all: SingleSparseReal FastSingleSparseReal FastSingleSparseComplex SingleSparseComplex MultiSparseReal MultiSparseComplex MultiDenseReal MultiDenseComplex KMeans DFT clean

SingleSparseReal: common.o SingleSparseReal.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

FastSingleSparseReal: common.o FastSingleSparseReal.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

FastSingleSparseComplex: common.o FastSingleSparseComplex.o
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

KMeans: common.o KMeans.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

DFT: common.o DFT.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

common.o: common.c common.h
	$(CC) $(CFLAGS) -c common.c $(LIBS)

clean: 
	rm -f *.o *.~

