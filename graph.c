// graph.c ... Graph of strings (adjacency matrix)
// Written by John Shepherd, September 2015
// taken from lab 8: https://cgi.cse.unsw.edu.au/~cs1927/17s1/labs/week08/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "graph.h"

#define strEQ(g,t) (strcmp((g),(t)) == 0)

//typedef unsigned char Num;

/*typedef struct GraphRep {
	int   nV;
	int   maxV;
	char  **vertex;
	Num   **edges;
} GraphRep;
*/
// Function signatures

Graph newGraph();
void  disposeGraph(Graph);
int   addEdge(Graph,char *,char *);
int   nVertices(Graph);
int   isConnected(Graph, char *, char *);
void  showGraph(Graph,int);
int outDegree(Graph, char *);

static int vertexID(char *, char **, int);
int addVertex(char *, char **, int);

// newGraph()
// - create an initially empty Graph
Graph newGraph(int maxV)
{
	Graph new = malloc(sizeof(GraphRep));
	assert(new != NULL);
	int i, j;
	new->nV = 0;
	new->maxV = maxV;
	new->vertex = malloc(maxV*sizeof(char *));
	assert(new->vertex != NULL);
	new->edges = malloc(maxV*sizeof(Num *));
	assert(new->edges != NULL);
	for (i = 0; i < maxV; i++) {
		new->vertex[i] = NULL;
		new->edges[i] = malloc(maxV*sizeof(Num));
		assert(new->edges[i] != NULL);
		for (j = 0; j < maxV; j++)
			new->edges[i][j] = 0;
	}
	return new;
}

// disposeGraph(Graph)
// - clean up memory associated with Graph
void disposeGraph(Graph g)
{
	if (g == NULL) return;
	int i;
	for (i = 0; i < g->nV; i++) {
		free(g->vertex[i]);
	}
	for (i = 0; i < g->maxV; i++) {
		free(g->edges[i]);
	}
	free(g->edges);
	free(g->vertex);
	free(g);
}

// addEdge(Graph,Src,Dest)
// - add an edge from Src to Dest
// - returns 1 if edge successfully added
// - returns 0 if unable to add edge
//   (usually because nV exceeds maxV)
int addEdge(Graph g, char *src, char *dest)
{
	assert(g != NULL);
	int v = vertexID(src,g->vertex,g->nV);
	if (v < 0) {
		if (g->nV >= g->maxV) return 0;
		v = addVertex(src,g->vertex,g->nV);
		g->nV++;
	}
	int w = vertexID(dest,g->vertex,g->nV);
	if (w < 0) {
		if (g->nV >= g->maxV) return 0;
		w = addVertex(dest,g->vertex,g->nV);
		g->nV++;
	}
	g->edges[v][w] = 1;
	return 1;
}

// outDegree(Graph, vertex)
// - return number of edges going from vertex to another vertex
// - doesn't include self-loops
int outDegree(Graph g, char *vertex)
{
	assert(g != NULL);
	int v = vertexID(vertex, g->vertex, g->nV);
	if (v < 0) {
		return -1;
	}
	int degree = 0;
	int i;
	for (i = 0; i < g->nV; i++) {
		if (i == v) continue; // don't count self-loops
		if (g->edges[v][i] != 0) {
			degree++;
		}
	}
	return degree;
}

// isConnected(Graph,Src,Dest)
// - check whether there is an edge from Src->Dest
int isConnected(Graph g, char *src, char *dest)
{
	assert(g != NULL);
	int v = vertexID(src,g->vertex,g->nV);
	int w = vertexID(dest,g->vertex,g->nV);
	if (v < 0 || w < 0)
		return 0;
	else
		return g->edges[v][w];
}

// nVertices(Graph)
// - return # vertices currently in Graph
int nVertices(Graph g)
{
	assert(g != NULL);
	return (g->nV);
}

// showGraph(Graph)
// - display Graph
void showGraph(Graph g, int mode)
{
	assert(g != NULL);
	if (g->nV == 0)
		printf("Graph is empty\n");
	else {
		printf("Graph has %d vertices:\n",g->nV);
		int i, j;
		if (mode == 1) {
			for (i = 0; i < g->nV; i++) {
				for (j = 0; j < g->nV; j++)
					printf("%d",g->edges[i][j]);
				putchar('\n');
			}
		}
		else {
			for (i = 0; i < g->nV; i++) {
				printf("Vertex: %s ", g->vertex[i]);
				int printed = 0;
				for (j = 0; j < g->nV; j++) {
					if (g->edges[i][j]) {
						if (!printed) {
							printf("connects to\n");
							printed = 1;
						}
						printf("   %s\n",g->vertex[j]);
					}
				}
				if (!printed)
					printf("has no connections\n");
			}
		}
	}
}

// Helper functions

// vertexID(Str,Names,N)
// - searches for Str in array of Names[N]
// - returns index of Str if found, -1 if not
static int vertexID(char *str, char **names, int N)
{
	int i;
	for (i = 0; i < N; i++)
		if (strEQ(str,names[i])) return i;
	return -1;
}

// addVertex(Str,Names,N)
// - add Str at end of Names
int addVertex(char *str, char **names, int N)
{
	names[N] = strdup(str);
	return N;
}
