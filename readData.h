#ifndef READDATA_H
#define READDATA_H

#include "graph.h"
#include "llist.h"
#include "BSTree.h"
List GetCollection();

List GetOutgoingUrls(char *);

List getList(FILE *);

void normalise(char *);

Graph GetGraph(void);

BSTree GetInvertedList(List);

#endif
