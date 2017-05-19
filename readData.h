#ifndef READDATA_H
#define READDATA_H

#include "graph.h"
#include "llist.h"
#include "BSTree.h"
List GetCollection();

List GetOutgoingUrls(char *);

Graph GetGraph(List);

BSTree GetInvertedList(List);

#endif
