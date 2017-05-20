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
#include "llist.h"
#include "graph.h"

#define EPSILON 1E-6

typedef struct URL{
	float pagerank;
	int nOutgoing;
	char *name;
} *URL;

void calculatePageRank(Graph,List,float, float, int);
void OutputToFile(Graph,List, float *);

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

	float d, diffPR;
	int maxIterations;
	d = atof(argv[1]);
	diffPR = atof(argv[2]);
	maxIterations = atoi(argv[3]);

	// GetCollection & GetGraph
	List l = GetCollection();
	showList(l);
	Graph g = GetGraph(l);
//	showGraph(g,0);

	calculatePageRank(g,l,d,diffPR,maxIterations);

	disposeGraph(g);
	destroyList(l);

	return EXIT_SUCCESS;
}

void calculatePageRank(Graph g,List l, float d, float diffPR, int maxIterations){
	int N = nVertices(g);
	float sum, diff, PR[N];

	int prOld;
	int i=0,j=0;
	// for each url PR[i] in the collection
	Node cur = NULL;
	while((cur = next(l,cur)) != NULL){
		PR[i] = 1/(float) N;
		i++;
	}
	int iteration = 0;
	diff = diffPR; // to enter the following loop

	while(iteration < maxIterations && diff >= diffPR) {
		iteration++;
		Node u = NULL;
		while((u = next(l,u))){ //for each url
			prOld = PR[i];
			sum = 0; // initialize sum
			while((cur = next(l,cur))!= NULL){
				if(isConnected(g,nodeValue(cur),nodeValue(u))){ // check if there is a connection between page i and j
					sum += PR[j] / outDegree(g,nodeValue(cur)); // increment sum
			}	
			j++;
			}
				PR[i] = (1-d)/N + d*sum; // add dampening factor
				diff += fabs(PR[i] - prOld); // convergence is assumed
			i++;}
	
	}
	OutputToFile(g,l, PR);
}

void OutputToFile(Graph g, List l,float *PR){
	int i=0; 
	int N=nVertices(g);
	URL array[N]; // array of pageranks
	Node cur = NULL;
	while((cur = next(l,cur))!=NULL){
		URL new = malloc(sizeof(URL));
		new->pagerank = PR[i];
		new->nOutgoing = outDegree(g,nodeValue(cur));
		new->name = strdup(nodeValue(cur));
		array[i] = new;
	i++;
	}
	myMergeSort((void*)array, 0, nVertices(g)-1, sizeof(URL), CompareOutgoing);
	myMergeSort((void*)array, 0, nVertices(g)-1, sizeof(URL), ComparePageRank);

	FILE*fp;
	if((fp = fopen("pagerankList.txt","w")) != NULL) {
		for(i=0;i<N;i++){
			printf("%s, %d, %.8f\n", array[i]->name, array[i]->nOutgoing, array[i]->pagerank);
			fprintf(fp, "%s, %d, %.8f\n", array[i]->name, array[i]->nOutgoing, array[i]->pagerank);
			free(array[i]->name);
			free(array[i]);
		}
		fclose(fp);
	}
}
