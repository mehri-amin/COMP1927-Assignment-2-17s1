CC = gcc
CFLAGS = -Wall -Werror -g

all: pagerank.o graph.o myMergeSort.o readData.o
	$(CC) $(CFLAGS) -o pagerank pagerank.o graph.o myMergeSort.o readData.o

readData.o: readData.c readData.h
	$(CC) -c $(CFLAGS) readData.c

graph.o: graph.c graph.h
	$(CC) -c $(CFLAGS) graph.c

pagerank.o: pagerank.c
	$(CC) -c $(CFLAGS) pagerank.c

myMergeSort.o: myMergeSort.c myMergeSort.h
	$(CC) -c $(CFLAGS) myMergeSort.c

clean :
	rm -f pagerank *.o core
