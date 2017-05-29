CC = gcc
CFLAGS = -Wall -Werror -g -lm

all: pagerank inverted searchTfIdf

pagerank: pagerank.o graph.o myMergeSort.o readData.o llist.o BSTree.o
	$(CC) $(CFLAGS) -o pagerank pagerank.o graph.o myMergeSort.o readData.o llist.o BSTree.o

searchTfIdf: searchTfIdf.o graph.o BSTree.o readData.o llist.o myMergeSort.o
	$(CC) $(CFLAGS) -o searchTfIdf searchTfIdf.o graph.o BSTree.o readData.o llist.o myMergeSort.o

searchTfIdf.o: searchTfIdf.c
	$(CC) -c $(CFLAGS) searchTfIdf.c

inverted: inverted.o readData.o graph.o llist.o BSTree.o
	$(CC) -o inverted inverted.o readData.o graph.o llist.o BSTree.o

inverted.o: inverted.c
	$(CC) -c $(CFLAGS) inverted.c

readData.o: readData.c readData.h
	$(CC) -c $(CFLAGS) readData.c

BSTree.o: BSTree.c BSTree.h
	$(CC) -c $(CFLAGS) BSTree.c

llist.o: llist.c llist.h
	$(CC) -c $(CFLAGS) llist.c

graph.o: graph.c graph.h
	$(CC) -c $(CFLAGS) graph.c

pagerank.o: pagerank.c
	$(CC) -c $(CFLAGS) pagerank.c

myMergeSort.o: myMergeSort.c myMergeSort.h
	$(CC) -c $(CFLAGS) myMergeSort.c

clean :
	rm -f pagerank *.o core inverted
