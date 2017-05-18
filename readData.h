#ifndef READDATA_H
#define READDATA_H

#include "graph.h"

typedef struct Node {
	char *val;
	struct Node *next;
} *Node;

typedef struct ListHead {
	struct Node *head;
	int length;

} *List;

Node newNode(char *);

char *nodeValue(Node);

List newList();

void destoryList(List);

Node next(List,Node);

void listPrepend(List,Node);

int listLength(List);

void showList(List);

List GetCollection();

List GetOutgoingUrls(char *);

Graph GetGraph(List);

#endif
