#ifndef READDATA_H
#define READDATA_H

#include "graph.h"
#include "llist.h"
List GetCollection();

List GetOutgoingUrls(char *);

Graph GetGraph(List);

#endif
