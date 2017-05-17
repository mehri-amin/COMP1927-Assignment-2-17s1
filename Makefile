CC = gcc
CFLAGS = -Wall -g

all: readData pagerank

readData: readData.o graph.o
	$(CC) -o readData readData.o graph.o

readData.o: readData.c
	$(CC) -c $(CFLAGS) readData.c

graph.o: graph.c graph.h
	$(CC) -c $(CFLAGS) graph.c

pagerank.o: pagerank.c
	$(CC) -c $(CFLAGS) pagerank.c

mergeSort.o: mergeSort.c mergeSort.h
	$(CC) -c $(CFLAGS) mergeSort.c
