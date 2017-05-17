CC = gcc
CFLAGS = -Wall -g

all: readData

readData: readData.o graph.o
	$(CC) -o readData readData.o graph.o

readData.o: readData.c
	$(CC) -c $(CFLAGS) readData.c

graph.o: graph.c graph.h
	$(CC) -c $(CFLAGS) graph.c
