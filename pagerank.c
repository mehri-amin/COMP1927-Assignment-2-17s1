#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "myMergeSort.h"
#include "readData.h"
#include "llist.h"
#include "graph.h"

#define EPSILON 1E-6

typedef struct URL{
	double pagerank;
	int nOutgoing;
	char *name;
} *URL;

void calculatePageRank(Graph,List,double, double, int);
void OutputToFile(Graph,List, double *);

static int ComparePageRank(const void *a,const void *b){
	return (((URL)b)->pagerank - ((URL)a)->pagerank > EPSILON) ? 0 : 1;
}

static int CompareOutgoing(const void *a,const void *b){

	return ((((URL)b)->nOutgoing - ((URL)a)->nOutgoing) > 0) ? 0 : 1;
}

int main(int argc, char *argv[]){

	// get args: d, diffPR, maxIterations
	if(argc < 4){
		printf("Usage: %s d, diffPR, maxIterations\n", argv[0]);
		exit(0);
	}

	double d, diffPR;
	int maxIterations;
	d = atof(argv[1]);
	diffPR = atof(argv[2]);
	maxIterations = atoi(argv[3]);

	// GetCollection & GetGraph
	List l = GetCollection();
	showList(l);
	Graph g = GetGraph();
	showGraph(g,0);

	calculatePageRank(g,l,d,diffPR,maxIterations);

	disposeGraph(g);
	destroyList(l);

	return EXIT_SUCCESS;
}

void calculatePageRank(Graph g,List l, double d, double diffPR, int maxIterations){
	int N = nVertices(g);
	double sum, diff, PR[N], oldPR[N];

	int i=0,j=0;
	// for each url PR[i] in the collection
	for(i=0;i<N;i++)
		PR[i] = oldPR[i] = 1.0f/(double) N;

	int iteration = 0;
	diff = diffPR; // to enter the following loop

	while (iteration < maxIterations && diff >= diffPR) {
		iteration++;
		memcpy(oldPR, PR, sizeof(double) * N);
		diff = 0;
		for (i=0;i<N;i++){
			sum = 0; // initialize sum
			for(j=0;j<N;j++){
				if (i == j) continue;
				if (isConnected(g,g->vertex[j],g->vertex[i])) { // check if there is a connection between page i and j
					sum += oldPR[j] / (double)outDegree(g,g->vertex[j]); // increment sum
				}
			}
			PR[i] = (1.0f-d)/(double)N + d*sum; // add dampening factor
			diff += fabs(PR[i] - oldPR[i]); // convergence is assumed
		}
	}
	OutputToFile(g,l, PR);
}

void OutputToFile(Graph g, List l, double *PR){
	int i=0;
	int N=nVertices(g);
	URL array[N]; // array of pageranks
	for(i=0;i<N;i++){
		URL new = malloc(sizeof(struct URL));
		new->pagerank = PR[i];
		new->nOutgoing = outDegree(g,g->vertex[i]);
		new->name = strdup(g->vertex[i]);
		array[i] = new;
	}
	myMergeSort((void*)array, 0, nVertices(g)-1, sizeof(URL), CompareOutgoing);
	myMergeSort((void*)array, 0, nVertices(g)-1, sizeof(URL), ComparePageRank);

	FILE*fp;
	if((fp = fopen("pagerankList.txt","w")) != NULL) {
		for(i=0;i<N;i++){
			printf("%s, %d, %.7f\n", array[i]->name, array[i]->nOutgoing, array[i]->pagerank);
			fprintf(fp, "%s, %d, %.7f\n", array[i]->name, array[i]->nOutgoing, array[i]->pagerank);
			free(array[i]->name);
			free(array[i]);
		}
		fclose(fp);
	}
}
