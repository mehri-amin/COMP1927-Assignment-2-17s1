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
#include "stringSet.h"
#include "SetG.h"
#include "readData.h"

// Create a table of rank files that includes content of files
// Create a Set S that is the union of the table (use set.c?)
// Create an function to locate position of each node - index
// Find number of elements in each rank - |t|
// Find number of elements in Set  |S|
// Find best P{} - permute function
double bestScore;
List bestList;

// recursively permute through all combinations
void permute(Set urls, List rankA, List rankD, Set excluded, List selected) {
	if (excluded == NULL) {
		bestScore = -1.0;
		excluded = newStringSet();
	}
	if (selected == NULL) {
		selected = newList();
	}
	
	if (SetSize(urls) == SetSize(excluded)) {
//		printf("=======\n");
		// no more options, calculate.
		Node curr = NULL;
		double sum = 0;
		int pos = 1;
		int len = listLength(selected);
		while ((curr = next(selected, curr)) != NULL) {
			// W(C, P) for T1
			int idx = listIndex(rankA, nodeValue(curr));
			if (idx != -1) {
				idx++;
//				printf("%d/%d - %d/%d\n", idx, listLength(rankA), pos, len);
				sum += fabs((double)idx / listLength(rankA) - (double)pos / len);
			}
			// W(C, P) for T2
			idx = listIndex(rankD, nodeValue(curr));
			if (idx != -1) {
				idx++;
//				printf("%d/%d - %d/%d\n", idx, listLength(rankD), pos, len);
				sum += fabs((double)idx / listLength(rankD) - (double)pos / len);
			}
			pos++;
		}
		if (sum < bestScore || bestScore < 0) {
			if (bestScore >= 0) {
				// destroy list
				destroyList(bestList);
			}
			bestScore = sum;
			bestList = listCopy(selected);
		}
	}
	void *ptr = NULL;
	char *val = NULL;
	
	while ((val = (char*)SetNext(urls, &ptr)) != NULL) {
		if (SetMember(excluded, val)) continue;
		SetInsert(excluded, val);
	 	ListAppend(selected, val);	
		permute(urls, rankA, rankD, excluded, selected);
		listDelete(selected);
		SetDelete(excluded, val);
	}

}
int main(int argc, char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "Usage: %s rankA rankD\n", argv[0]);
		return 0;
	}
	List rankA;
	List rankD;
	int i;
	for (i=1; i<argc; i++) {
		FILE *f = fopen(argv[i], "r");
		if (i == 1) {
			rankA = getList(f);
		} else {
			rankD = getList(f);
		}
		fclose(f);
	}
	Set urls = newStringSet();
	Node curr = NULL;
	while ((curr = next(rankA, curr)) != NULL) {
		SetInsert(urls, nodeValue(curr));
	}
	while ((curr = next(rankD, curr)) != NULL) {
		SetInsert(urls, nodeValue(curr));
	}
	permute(urls, rankA, rankD, NULL, NULL);
	printf("%f\n", bestScore);
	curr = NULL;
	while ((curr = next(bestList, curr)) != NULL) {
		printf("%s\n", nodeValue(curr));
	}
	return 0;
}


/*
static double calcScaledFR(int P[], int |t|, int |S|, char ***Table, char **elements){
	return result;
}
*/
