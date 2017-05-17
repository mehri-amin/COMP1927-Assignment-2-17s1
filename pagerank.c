/* pagerank.c

	- Get args : d, diffPR, maxIterations
	
	- GetCollection
	- GetGraph

	- List_Urls_PageRanks = calculatePageRank(g,d,diffPR,maxIterations)
	- Ordered_List_Urls_PageRanks = order(List_Urls_PageRanks)

	- Output Ordered_List_Urls_PageRanks to "pagerankList.txt"

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mergesort.h"	
#include "readData.h"
#include "graph.h"

#define EPSILON 1E-6

typedef struct URL{
	float pagerank;
	int nOutgoing;
	char *name;
} *URL;

void calculatePageRank(Graph, float, float, int);
void OutputToFile(Graph, float *);

static int CompareURLs(const void *a, const void *b){
	if(((nPageRank)b)->PR - ((nPageRank)a)->PR < EPSILON) return -1;
	else return 0;

	if((((nPageRank)b)->nOutgoing - ((nPageRank)a)->nOutgoing) < 0) return -1;
	else return 0;
}

int main(int argc, char *argv[]){
	
	// get args: d, diffPR, maxIterations
	assert(argv == 4)
	float d, diffPR;
	int maxIterations;
	d = atof(argv[1]);
	diffPR = atof(argv[2]);
	maxIterations = atoi(argv[3]);
	
	// GetCollection & GetGraph
	List List_of_Urls = newList(); 
	GetCollection(List_of_Urls);
	Graph g = newGraph(listLength(List_of_Urls));
	GetGraph(List_of_Urls);

	calculatePageRank(g,d,diffpR,maxIterations);

	OutputToFile(g, PageRank);	

	disposeGraph(g);
	destroyList(List List_of_Urls);
	
	return 1;
}

void calculatePageRank(Graph g, float d, float diffPR, int maxIterations){
	int i, j, N = nVertices(g);
	float sum, PR[N];
	
	for(i=0; i<N; i++)
		PR[i] = 1/N; //default
	
	int iteration = 0;
	diff = diffPR; // to enter the following loop

	while(iteration < maxIterations && diff >= diffPR)
			
		iteration++;
		for(i=0; i<N; i++){
		sum = 0;
			for(j=0; j<N; j++){
			if(isConnected(g, g->vertex[i], g->vertex[j]));
			sum += PR[j] / nEdges(g,j);
			}
		PR[i] = (1-d)/N + d*sum;
		diff += fabs(PR[i] - PR[i-1]);
		}

}

void OutputToFile(Graph g, float *PageRank){
	int i, N=nVertices(g);
	URL PageRanks[];
	
	for(i=0; i<N; i++){
		URL new = malloc(sizeof(URL));
		new->pagerank = PR[i];
		new->nOutgoing = nEdges(g,i);
		new->name = strdup(g->vertex[i]);
		PageRanks[i] = new;
	}

	mergesort((void*PageRanks, 0, nVertices(g)-1, sizeof(URL), CompareURLs);
	
	FILE*fp;
	if((fp = fopen("pagerankList.txt","w")) != NULL) {
		for(i=0; i<N; i++){
		printf("%s, %d, %.8f\n", PageRanks[i]->name, PageRanks[i]->nOutgoing, PageRanks[i]->PR);
		fprintf(fp, "%s, %d, %.8f\n", PageRanks[i]->name, PageRanks[i]->nOutgoing, PageRanks[i]->PR);
		free(PageRanks[i]->name);
		free(PageRanks[i]);
		}
	fclose(fp);
	}
}
