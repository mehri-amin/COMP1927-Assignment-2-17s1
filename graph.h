// graph.h ... Interface to Graph of strings
// Written by John Shepherd, September 2015
// Taken from lab 8: https://cgi.cse.unsw.edu.au/~cs1927/17s1/labs/week08/

#ifndef GRAPH_H
#define GRAPH_H
typedef unsigned char Num;
typedef struct GraphRep{
	int nV;
	int maxV;
	char **vertex;
	Num **edges;
}GraphRep;

typedef struct GraphRep *Graph;

// Function signatures

Graph newGraph(int);
void  disposeGraph(Graph);
int   addEdge(Graph,char *,char *);
int   nVertices(Graph);
int   isConnected(Graph, char *, char *);
void  showGraph(Graph,int);
int outDegree(Graph, char *);
#endif

