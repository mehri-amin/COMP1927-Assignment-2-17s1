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
#include <string.h>
#include "myMergeSort.h"
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

static int ComparePageRank(void *a, void *b){
	if(((URL)b)->pagerank - ((URL)a)->pagerank > EPSILON) return 0;
	else return 1;
}

static int CompareOutgoing(void *a, void *b){

	if((((URL)b)->nOutgoing - ((URL)a)->nOutgoing) > 0) return 0;
	else return 1;
}

int main(int argc, char *argv[]){

	// get args: d, diffPR, maxIterations
	if(argc < 4){
		printf("Usage: %s d, diffPR, maxIterations\n", argv[0]);
		exit(0);
	}

	float d, diffPR;
	int maxIterations;
	d = atof(argv[1]);
	diffPR = atof(argv[2]);
	maxIterations = atoi(argv[3]);

	// GetCollection & GetGraph
	List urls = GetCollection();
	showList(urls);
	Graph g = GetGraph(urls);
	showGraph(g,0);

	calculatePageRank(g,d,diffPR,maxIterations);

	destroyList(urls);
	disposeGraph(g);

	return EXIT_SUCCESS;
}

void calculatePageRank(Graph g, float d, float diffPR, int maxIterations){
	int i, j, N = nVertices(g);
	float sum, diff, PR[N];

	// for each url PR[i] in the collection
	for(i=0; i<N; i++)
		PR[i] = 1/N;

	int iteration = 0;
	diff = diffPR; // to enter the following loop

	while(iteration < maxIterations && diff >= diffPR)

		iteration++;
		for(i=0; i<N; i++){ //for each url
		sum = 0; // initialize sum
			for(j=0; j<N; j++){ //for each page pointing to PR[i]
			if(isConnected(g,g->vertex[j],g->vertex[i])){ // check if there is a connection between page i and j
			sum += PR[j] / outDegree(g,g->vertex[j]); // increment sum
			}
		PR[i] = (1-d)/N + d*sum; // add dampening factor
		diff += fabs(PR[i] - PR[i-1]); // convergence is assumed
		}
	}
	OutputToFile(g, PR);
}

void OutputToFile(Graph g, float *PR){
	int i, N=nVertices(g);
	URL array[N]; // array of pageranks

	for(i=0; i<N; i++){
		URL new = malloc(sizeof(URL));
		new->pagerank = PR[i];
		new->nOutgoing = outDegree(g,g->vertex[i]);
		new->name = strdup(g->vertex[i]);
		array[i] = new;
	}

	myMergeSort((void*)array, 0, nVertices(g)-1, sizeof(URL), CompareOutgoing);
	myMergeSort((void*)array, 0, nVertices(g)-1, sizeof(URL), ComparePageRank);

	FILE*fp;
	if((fp = fopen("pagerankList.txt","w")) != NULL) {
		for(i=0; i<N; i++){
		printf("%s, %d, %.8f\n", array[i]->name, array[i]->nOutgoing, array[i]->pagerank);
		fprintf(fp, "%s, %d, %.8f\n", array[i]->name, array[i]->nOutgoing, array[i]->pagerank);
		free(array[i]->name);
		free(array[i]);
		}
	fclose(fp);
	}
}
