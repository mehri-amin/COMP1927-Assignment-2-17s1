// Part 3: Hybrid/Meta Search Engine using Rank Aggregation

/* 
	Let T1 and T2 be search results (ranks) obtained from Part-1
	and Part-2 respectively. 

	Let S be a union of T1 and T2.

	Weighted Bipartite - (C,P,W)
		C = set of nodes to be ranked
		P = set of positions available
		W(c,p) = scaled-footrule distance given by
			sum |ti(c)/|ti| - p\n|
			n = |S|

Some stuff I found that could help in making a smart Algorithm:
	- Spearman's Rank Correlation Coefficient
	- Maximum (Minimum) Cost of Weighted Bipartites 
	- Kendall Tau Distance

*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>

int RankArray(char*, char***);
void permute(
int Position(char**,char*,int);
double calcScaledFR(


int main(int argc, char *argv[])
{
	if(argc < 2){
	fprintf(stderr, "Usage: rankA rankD...\n");
	exit(0);
	}

	Set S = malloc(sizeof(Set) * (argc - 1));
	for(i=1; i<argc; i++) S[] = getCollection(argv[i]);
}

// Create a table of rank files that includes content of files
// Create a Set S that is the union of the table (use set.c?)
// Create an function to locate position of each node - index
// Find number of elements in each rank - |t|
// Find number of elements in Set  |S|
// Find best P{} - permute function

void permute(char *a, int i, int n, position, Set S)
	if(i==n) 
	printf
	else for(j = i; j<=n; j++)
	swap, permute, swap

static double calcScaledFR(int P[], int |t|, int |S|, char ***Table, char **elements){
	double result = 0;
	int i,j;
	for(i=0; i<|S|;i++){
		for(j=0;j<int|t|;j++){
			int T(c) = findposition();
			result += | (T(c)/|t| - P[]/|S|) |;

	return result;
}

