#ifndef READDATA_H
#define READDATA_H

#include "graph.h"
#include "llist.h"
#include "BSTree.h"
List GetCollection();

List GetOutgoingUrls(char *);

List getList(FILE *);

Graph GetGraph();

BSTree GetInvertedList(List);

#endif
